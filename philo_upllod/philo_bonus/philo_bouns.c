/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bouns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:47:48 by abin-saa          #+#    #+#             */
/*   Updated: 2022/12/05 08:06:18 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind  --leak-check=full --trace-children=yes ./philo_bouns 4 310 200 100
#include "philo_bouns.h"

void	creat_philo(t_philo	*philo, t_ephilo *e_ph)
{
	int	i;

	i = 0;
	while (i < philo->num)
	{
		philo->process[i] = fork();
		if (philo->process[i] == 0)
		{
			e_ph->id_p = i;
			e_ph->og = philo;
			e_ph->eat_con = 0;
			e_ph->time_last_maill = 0;
			pthread_create(&philo->cheak_deth, NULL, cheak_death, e_ph);
			philo_live(e_ph);
		}
		i++;
	}
}

int	death(t_ephilo *philo)
{
	sem_wait(philo->og->semphor_time);
	sem_wait(philo->og->semphor_status);
	if (philo->og->full_mail == 1)
	{
		sem_post(philo->og->semphor_status);
		sem_post(philo->og->semphor_time);
		return (0);
	}
	if (philo->og->time_die <= get_time() - philo->time_last_maill
		&& philo->og->if_dead == 0)
	{
		philo->og->if_dead = 1;
		if (philo->og->if_dead == 1)
		{
			printf("%d is dead Time: %lld\n",
				philo->id_p + 1, get_time() - philo->og->curnt_time);
			return (0);
		}
	}
	sem_post(philo->og->semphor_status);
	sem_post(philo->og->semphor_time);
	usleep(100);
	return (1);
}

void	*cheak_death(void *param)
{
	t_ephilo		*philo;

	philo = param;
	while (1)
	{
		if (death(philo) == 0)
			return (0);
	}
	return (0);
}

int	philo_live(t_ephilo *philo)
{
	philo->time_last_maill = philo->og->curnt_time;
	while (1)
	{
		if (philo->og->if_dead == 1)
			ft_exit(philo);
		ft_eat(philo);
		time_musteat(philo);
		if (philo->og->if_dead == 0)
		{
			sem_wait(philo->og->semphor_status);
			printf("%lld %d is sleep\n",
				get_time() - philo->og->curnt_time, philo->id_p + 1);
			sem_post(philo->og->semphor_status);
		}
		ft_usleep(philo, philo->og->time_sleep);
		if (philo->og->if_dead == 0)
		{
			sem_wait(philo->og->semphor_status);
			printf("%lld %d is the king\n",
				get_time() - philo->og->curnt_time, philo->id_p + 1);
			sem_post(philo->og->semphor_status);
		}
	}
}

int	main(int ac, char **av)
{
	t_ephilo	e_ph;
	t_philo		philo;

	cheak_c(ac, &av);
	cheack_arg(ac, av);
	if (ft_atoi(av[1]) == 1)
	{
		usleep(ft_atoi(av[2]) * 1000);
		printf("%s philo   %d is dead ", av[2], 1);
		return (0);
	}
	crate_v(ac, av, &philo);
	creat_philo(&philo, &e_ph);
	if (ac == 5)
		kill_all(&philo);
	if (ac == 6)
		kill_all2(&philo);
}
