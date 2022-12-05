/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls2_bouns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:58:34 by abin-saa          #+#    #+#             */
/*   Updated: 2022/11/25 07:56:20 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bouns.h"

void	ft_exit( t_ephilo *philo)
{
	sem_unlink("time");
	sem_unlink("forks");
	sem_unlink("status");
	sem_close(philo->og->semphor_status);
	sem_close(philo->og->semphor);
	sem_close(philo->og->semphor_time);
	pthread_detach(philo->og->cheak_deth);
	free(philo->og->exitcode);
	free(philo->og->process);
	exit(127);
}

long long	get_time(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	ft_usleep(t_ephilo *philo, long long sleep)
{
	long long	start_time2;
	long long	elapsed_time;

	start_time2 = get_time();
	elapsed_time = 0;
	while (elapsed_time < sleep)
	{
		if (philo->og->if_dead == 1
			||philo->og->time_die <= get_time() - philo->time_last_maill)
		{
			sem_post(philo->og->semphor);
			sem_post(philo->og->semphor);
			pthread_join(philo->og->cheak_deth, NULL);
			sem_unlink("time");
			sem_unlink("forks");
			sem_unlink("status");
			sem_close(philo->og->semphor_status);
			sem_close(philo->og->semphor);
			sem_close(philo->og->semphor_time);
			free(philo->og->exitcode);
			free(philo->og->process);
			exit(127);
		}
		elapsed_time = get_time() - start_time2;
	}
}

int	cheak_c(int ac, char ***av)
{
	int	i;
	int	c;

	i = 1;
	c = 0;
	if (ac != 5 && ac != 6)
		exit (1);
	while (ac - 1 >= i)
	{
		c = 0;
		while ((*av)[i][c] != '\0')
		{
			if (ft_isdigit((*av)[i][c]) == 0)
			{
				write(2, "Error", 5);
				exit(1);
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
	philo->exitcode = ft_calloc(ft_atoi(av[1]), sizeof(int));
	philo->last_philo = (philo->num - 1);
	philo->curnt_time = get_time();
	philo->ac = ac;
	philo->last_philo = (philo->num - 1);
	philo->if_dead = 0;
	philo->process = ft_calloc(philo->num, sizeof(int));
	philo->full_mail = 0;
	sem_unlink("time");
	sem_unlink("forks");
	sem_unlink("status");
	philo->semphor = sem_open("forks", O_CREAT, 0644, ft_atoi(av[1]));
	philo->semphor_time = sem_open("time", O_CREAT, 0644, 1);
	philo->semphor_status = sem_open("status", O_CREAT, 0644, 1);
}
