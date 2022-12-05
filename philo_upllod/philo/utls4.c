/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:17:36 by abin-saa          #+#    #+#             */
/*   Updated: 2022/12/05 07:57:21 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cheak_c(int ac, char ***av)
{
	int	i;
	int	c;

	i = 1;
	c = 0;
	if (ac != 5 && ac != 6)
		return (0);
	while (ac - 1 >= i)
	{
		c = 0;
		while ((*av)[i][c] != '\0')
		{
			if (ft_isdigit((*av)[i][c]) == 0)
			{
				write(2, "Error", 5);
				return (0);
			}
			c++;
		}
		i++;
	}
	return (1);
}

void	crate_v(int ac, char **av, t_philo *philo)
{
	philo->num = ft_atoi(av[1]);
	philo->time_die = (ft_atoi(av[2]));
	philo->time_eat = (ft_atoi(av[3]));
	philo->time_sleep = (ft_atoi(av[4]));
	philo->mail_limet = 0;
	if (ac == 6)
		philo->mail_limet = (ft_atoi(av[5]));
	philo->last_philo = (philo->num - 1);
	philo->curnt_time = get_time();
	philo->ac = ac;
	philo->last_philo = (philo->num - 1);
	philo->if_dead = 0;
	philo->last_use = ft_calloc(sizeof(int), philo->num);
	philo->forks = ft_calloc(sizeof(int), philo->num);
	philo->phil = ft_calloc(sizeof(pthread_t), ft_atoi(av[1]));
	philo->mutex_forks = ft_calloc(sizeof(pthread_mutex_t), philo->num);
	pthread_mutex_init(&philo->mutex_dead, NULL);
	pthread_mutex_init(&philo->mutex_prinf, NULL);
	pthread_mutex_init(&philo->limts, NULL);
}

int	cheack_arg(int ac, char **av)
{
	if (ft_atoi(av[1]) > 200)
	{
		write(2, "Error", 5);
		return (0);
	}
	if (ft_atoi(av[1]) == 0 || ft_atoi(av[2]) == 0
		|| ft_atoi(av[3]) == 0 || ft_atoi(av[4]) == 0)
	{
		write(2, "Error", 5);
		return (0);
	}
	if (ac == 6)
	{
		if (ft_atoi(av[5]) == 0)
		{
			write(2, "Error", 5);
			return (0);
		}
	}
	return (1);
}
