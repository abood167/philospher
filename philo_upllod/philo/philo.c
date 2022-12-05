/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:43:46 by abin-saa          #+#    #+#             */
/*   Updated: 2022/12/05 08:00:33 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*rr(void *param)
{
	t_ephilo	*philo;
	long long	start_time;
	int			i;

	philo = param;
	start_time = philo->og->curnt_time;
	philo->time_last_maill = start_time;
	while (1)
	{
		i = philo->id_p;
		if (cheack_death(philo, start_time) == 0)
			return (0);
		if (helper(philo, i, start_time) == 0)
			return (0);
		if (helper3(philo) == 0)
			return (0);
		usleep(100);
	}
	return (0);
}

void	crate_th( t_ephilo **e_ph, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->num)
		pthread_mutex_init(&philo->mutex_forks[i], NULL);
	i = 0;
	while (i < philo->num)
	{
		(*e_ph)[i].id_p = i;
		(*e_ph)[i].og = philo;
		(*e_ph)[i].eat_con = 0;
		if (i == philo->last_philo)
		{
			(*e_ph)[i].left = 0;
			(*e_ph)[i].right = i;
		}
		else
		{
			(*e_ph)[i].left = i;
			(*e_ph)[i].right = i + 1;
		}
		pthread_create((&philo->phil[i]), NULL, rr, &(*e_ph)[i]);
		i++;
	}
}

int	cheak_helper(t_philo *philo, t_ephilo **e_ph, int *all_ate)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->mutex_dead);
	if (philo->if_dead == 1)
	{
		pthread_mutex_unlock(&philo->mutex_dead);
		return (0);
	}
	pthread_mutex_unlock(&philo->mutex_dead);
	*all_ate = 1;
	i = 0;
	while (i < philo->num)
	{
		pthread_mutex_lock(&philo->limts);
		if ((*e_ph)[i].eat_con < philo->mail_limet)
		{
			*all_ate = 0;
			pthread_mutex_unlock(&philo->limts);
		}
		else
			pthread_mutex_unlock(&philo->limts);
		i++;
	}
	return (1);
}

void	cheak_mills(t_philo *philo, int ac, t_ephilo **e_ph)
{
	int	all_ate;

	while (1)
	{
		if (cheak_helper(philo, e_ph, &all_ate) == 0)
			return ;
		if (ac == 6 && all_ate == 1)
		{
			pthread_mutex_lock(&philo->mutex_dead);
			philo->if_dead = 1;
			pthread_mutex_unlock(&philo->mutex_dead);
			break ;
		}
	}
}

int	main(int ac, char **av)
{
	int			i;
	t_ephilo	*e_ph;
	t_philo		philo;

	if (cheak_c(ac, &av) == 0)
		return (0);
	if (cheack_arg(ac, av) == 0)
		return (0);
	if (ft_atoi(av[1]) == 1)
	{
		usleep(ft_atoi(av[2]) * 1000);
		printf("%s philo   %d is dead ", av[2], 1);
		return (0);
	}
	e_ph = ft_calloc(sizeof(t_ephilo), ft_atoi(av[1]));
	crate_v(ac, av, &philo);
	crate_th(&e_ph, &philo);
	cheak_mills(&philo, ac, &e_ph);
	i = -1;
	while (philo.num > ++i)
		pthread_join(philo.phil[i], NULL);
	ft_exit(&philo, e_ph);
	return (0);
}
