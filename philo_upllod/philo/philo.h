/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:41:04 by abin-saa          #+#    #+#             */
/*   Updated: 2022/11/24 15:33:10 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>

typedef struct s_philo
{
	int					num;
	int					ac;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					*forks;
	int					*last_use;
	int					mail_limet;
	int					kkkk;
	int					last_philo;
	int					if_dead;
	long long			curnt_time;
	pthread_mutex_t		*mutex_forks;
	pthread_mutex_t		mutex_prinf;
	pthread_mutex_t		mutex_dead;
	pthread_mutex_t		limts;
	pthread_t			*phil;

}t_philo;

typedef struct s_phil
{
	int			id_p;
	long long	time_last_maill;
	int			eat_con;
	int			right;
	int			left;
	t_philo		*og;
}t_ephilo;

void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
int			ft_isdigit(int c);
void		take_forks(t_ephilo *philo, int i);
void		eat(t_ephilo *philo, int i, long long start_time);
void		ft_sleep(t_ephilo *philo, int i, long long start_time);
int			helper2(t_ephilo *philo, int i, long long start_time);
int			helper(t_ephilo *philo, int i, long long start_time);
void		ft_exit(t_philo *philo, t_ephilo *e_ph);
long long	get_time(void);
int			cheack_death(t_ephilo *philo, long long start_time);
int			ft_usleep(t_ephilo *philo, long long sleep, long long start_time);
int			helper3(t_ephilo *philo);
void		crate_v(int ac, char **av, t_philo *philo);
int			cheak_c(int ac, char ***av);
int			cheack_arg(int ac, char **av);
#endif