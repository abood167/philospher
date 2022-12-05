/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:05:03 by abin-saa          #+#    #+#             */
/*   Updated: 2022/11/24 14:12:42 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_ephilo *philo, int i)
{
	pthread_mutex_unlock(&philo->og->mutex_forks[philo->left]);
	pthread_mutex_unlock(&philo->og->mutex_forks[philo->right]);
	philo->time_last_maill = get_time();
	pthread_mutex_lock(&philo->og->mutex_forks[philo->left]);
	pthread_mutex_lock(&philo->og->mutex_forks[philo->right]);
	philo->og->forks[philo->left] = 1;
	philo->og->forks[(philo->right)] = 1;
	philo->og->last_use[philo->left] = i;
	philo->og->last_use[(philo->right)] = i;
	pthread_mutex_unlock(&philo->og->mutex_forks[philo->left]);
	pthread_mutex_unlock(&philo->og->mutex_forks[philo->right]);
}

void	eat(t_ephilo *philo, int i, long long start_time)
{
	pthread_mutex_lock(&philo->og->mutex_dead);
	if (philo->og->if_dead == 0)
	{
		pthread_mutex_lock(&philo->og->mutex_prinf);
		printf("%lld %d has take fork \n",
			get_time() - start_time, i + 1);
		printf("%lld %d has take fork \n",
			get_time() - start_time, i + 1);
		printf("%lld %d is eat\n",
			get_time() - start_time, i + 1);
		pthread_mutex_unlock(&philo->og->mutex_prinf);
		if (philo->og->ac == 6)
		{
			pthread_mutex_lock(&philo->og->limts);
			philo->eat_con += 1;
			pthread_mutex_unlock(&philo->og->limts);
		}
	}
	pthread_mutex_unlock(&philo->og->mutex_dead);
}

void	ft_sleep(t_ephilo *philo, int i, long long start_time)
{
	pthread_mutex_lock(&philo->og->mutex_forks[philo->left]);
	pthread_mutex_lock(&philo->og->mutex_forks[philo->right]);
	philo->og->forks[philo->left] = 0;
	philo->og->forks[philo->right] = 0;
	pthread_mutex_unlock(&philo->og->mutex_forks[philo->left]);
	pthread_mutex_unlock(&philo->og->mutex_forks[philo->right]);
	pthread_mutex_lock(&philo->og->mutex_dead);
	if (philo->og->if_dead == 0)
	{
		pthread_mutex_unlock(&philo->og->mutex_dead);
		pthread_mutex_lock(&philo->og->mutex_prinf);
		printf("%lld %d is sleep  cute\n",
			get_time() - start_time, i + 1);
		pthread_mutex_unlock(&philo->og->mutex_prinf);
	}
	else
		pthread_mutex_unlock(&philo->og->mutex_dead);
}

int	helper2(t_ephilo *philo, int i, long long start_time)
{
	take_forks(philo, i);
	if (cheack_death(philo, start_time) == 0)
		return (0);
	eat(philo, i, start_time);
	if (cheack_death(philo, start_time) == 0)
		return (0);
	ft_usleep(philo, philo->og->time_eat, start_time);
	if (cheack_death(philo, start_time) == 0)
		return (0);
	ft_sleep(philo, i, start_time);
	if (ft_usleep(philo, philo->og->time_sleep,
			start_time) == 0)
		return (0);
	pthread_mutex_lock(&philo->og->mutex_dead);
	if (philo->og->if_dead == 0)
	{
		pthread_mutex_unlock(&philo->og->mutex_dead);
		pthread_mutex_lock(&philo->og->mutex_prinf);
		printf("%lld  %d is thing\n",
			get_time() - start_time, i + 1);
		pthread_mutex_unlock(&philo->og->mutex_prinf);
	}
	else
		pthread_mutex_unlock(&philo->og->mutex_dead);
	return (1);
}

int	helper(t_ephilo *philo, int i, long long start_time)
{
	if (cheack_death(philo, start_time) == 0)
		return (0);
	pthread_mutex_lock(&philo->og->mutex_forks[philo->left]);
	pthread_mutex_lock(&philo->og->mutex_forks[philo->right]);
	if (philo->og->last_use[philo->left] != i
		&& philo->og->last_use[philo->right] != i)
	{
		if (philo->og->forks[philo->left] == 0
			&& philo->og->forks[philo->right] == 0)
		{
			helper2(philo, i, start_time);
		}
		else
		{
			pthread_mutex_unlock(&philo->og->mutex_forks[philo->left]);
			pthread_mutex_unlock(&philo->og->mutex_forks[philo->right]);
		}
	}
	else
	{
		pthread_mutex_unlock(&philo->og->mutex_forks[philo->left]);
		pthread_mutex_unlock(&philo->og->mutex_forks[philo->right]);
	}
	return (1);
}
