/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:11:22 by abin-saa          #+#    #+#             */
/*   Updated: 2022/11/24 15:28:46 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_philo *philo, t_ephilo *e_ph)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->limts);
	pthread_mutex_destroy(&philo->mutex_prinf);
	pthread_mutex_destroy(&philo->mutex_dead);
	while (i < philo->num)
	{
		pthread_mutex_destroy(&philo->mutex_forks[i]);
		i++;
	}
	free(philo->forks);
	free(philo->last_use);
	free(philo->mutex_forks);
	free(philo->phil);
	free(e_ph);
}

long long	get_time(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

int	cheack_death(t_ephilo *philo, long long start_time)
{
	long long	t1;

	t1 = get_time();
	pthread_mutex_lock(&philo->og->mutex_dead);
	if ((((philo->og->time_die) <= (t1 - philo->time_last_maill))
			&& philo->og->if_dead == 0))
	{
		philo->og->if_dead = 1;
		pthread_mutex_lock(&philo->og->mutex_prinf);
		printf("%lld  %d is dead\n", get_time() - start_time, philo->id_p + 1);
		pthread_mutex_unlock(&philo->og->mutex_prinf);
		pthread_mutex_unlock(&philo->og->mutex_dead);
		return (0);
	}
	if (philo->og->if_dead == 1)
	{
		pthread_mutex_unlock(&philo->og->mutex_dead);
		return (0);
	}
	pthread_mutex_unlock(&philo->og->mutex_dead);
	return (1);
}

int	ft_usleep(t_ephilo *philo, long long sleep, long long start_time)
{
	long long	start_time2;
	long long	elapsed_time;

	start_time2 = get_time();
	elapsed_time = 0;
	while (elapsed_time < sleep)
	{
		if (cheack_death(philo, start_time) == 0)
			return (0);
		elapsed_time = get_time() - start_time2;
		usleep(100);
	}
	return (1);
}

int	helper3(t_ephilo *philo)
{
	pthread_mutex_lock(&philo->og->mutex_dead);
	if (philo->og->if_dead == 1)
	{
		pthread_mutex_unlock(&philo->og->mutex_dead);
		return (0);
	}
	pthread_mutex_unlock(&philo->og->mutex_dead);
	return (1);
}
