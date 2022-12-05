/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls3_bouns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:51:12 by abin-saa          #+#    #+#             */
/*   Updated: 2022/12/05 08:17:20 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bouns.h"

void	kill_all(t_philo *philo)
{
	int	i;

	i = 0;
	waitpid(-1, &philo->exitcode[i], WUNTRACED);
	while (i < philo->num)
	{
		kill(philo->process[i], SIGKILL);
		i++;
	}
	sem_unlink("forks");
	sem_unlink("time");
	sem_unlink("status");
	sem_close(philo->semphor_status);
	sem_close(philo->semphor);
	sem_close(philo->semphor_time);
	free(philo->process);
	free(philo->exitcode);
	exit(0);
}

void	kill_all2(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		waitpid(-1, &philo->exitcode[i], 0);
		if (philo->exitcode[i] / 256 == 127)
		{
			while (i < philo->num)
			{
				kill(philo->process[i], 9);
				i++;
			}	
			break ;
		}
		if (i >= philo->num - 1)
			break ;
		i++;
	}
	sem_close(philo->semphor_time);
	sem_close(philo->semphor_status);
	sem_close(philo->semphor);
	sem_unlink("forks");
	sem_unlink("time");
	sem_unlink("status");
	free(philo->process);
	free(philo->exitcode);
	exit (0);
}

void	time_musteat(t_ephilo *philo)
{
	if (philo->og->if_dead == 1)
		ft_exit(philo);
	if (philo->og->ac == 6)
	{
		philo->eat_con++;
		if (philo->eat_con == philo->og->mail_limet)
		{
			philo->og->full_mail = 1;
			sem_unlink("time");
			sem_unlink("forks");
			sem_unlink("status");
			pthread_join(philo->og->cheak_deth, NULL);
			sem_close(philo->og->semphor_status);
			sem_close(philo->og->semphor);
			sem_close(philo->og->semphor_time);
			free(philo->og->exitcode);
			free(philo->og->process);
			exit(1);
		}
	}
	if (philo->og->if_dead == 1)
		ft_exit(philo);
}

void	ft_eat(t_ephilo *philo)
{
	sem_wait(philo->og->semphor);
	sem_wait(philo->og->semphor);
	if (philo->og->if_dead == 1)
		ft_exit(philo);
	philo->time_last_maill = get_time();
	if (philo->og->if_dead == 0)
	{
		if (philo->og->if_dead == 1)
			ft_exit(philo);
		sem_wait(philo->og->semphor_status);
		printf("%lld %d has take fork \n",
			get_time() - philo->og->curnt_time, philo->id_p + 1);
		printf("%lld %d has take fork \n",
			get_time() - philo->og->curnt_time, philo->id_p + 1);
		printf("%lld %d is eat\n",
			get_time() - philo->og->curnt_time, philo->id_p + 1);
		sem_post(philo->og->semphor_status);
	}
	if (philo->og->if_dead == 1)
		ft_exit(philo);
	ft_usleep(philo, philo->og->time_eat);
	if (philo->og->if_dead == 1)
		ft_exit(philo);
	sem_post(philo->og->semphor);
	sem_post(philo->og->semphor);
}

void	cheack_arg(int ac, char **av)
{
	if (ft_atoi(av[1]) > 200)
	{
		write(2, "Error", 5);
		exit(1);
	}
	if (ft_atoi(av[2]) == 0 || ft_atoi(av[3]) == 0
		|| ft_atoi(av[4]) == 0 || ft_atoi(av[1]) == 0)
	{
		write(2, "Error", 5);
		exit(1);
	}
	if (ac == 6)
	{
		if (ft_atoi(av[5]) == 0)
		{
			write(2, "Error", 5);
			exit(1);
		}
	}
}
