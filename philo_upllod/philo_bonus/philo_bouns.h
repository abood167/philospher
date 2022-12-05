/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bouns.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:30:36 by abin-saa          #+#    #+#             */
/*   Updated: 2022/11/25 07:27:59 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BOUNS_H
# define PHILO_BOUNS_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_phil
{
	int					num;
	int					ac;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					mail_limet;
	int					last_philo;
	int					if_dead;
	long long			curnt_time;
	int					*process;
	sem_t				*semphor;
	sem_t				*semphor_time;
	sem_t				*semphor_status;
	pthread_t			cheak_deth;
	int					full_mail;
	int					*exitcode;

}t_philo;

typedef struct s_philo
{
	int			id_p;
	long long	time_last_maill;
	int			eat_con;
	t_philo		*og;
}t_ephilo;

void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
int			ft_isdigit(int c);
void		ft_exit( t_ephilo *e_ph);
long long	get_time(void);
void		ft_usleep( t_ephilo *e_ph, long long sleep);
void		crate_v(int ac, char **av, t_philo *philo);
int			cheak_c(int ac, char ***av);
void		*cheak_death(void *param);
int			philo_live(t_ephilo *philo);
void		kill_all(t_philo *philo);
void		kill_all2(t_philo *philo);
void		time_musteat(t_ephilo *philo);
void		ft_eat(t_ephilo *philo);
void		cheack_arg(int ac, char **av);
#endif