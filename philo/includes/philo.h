/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:03:39 by agruet            #+#    #+#             */
/*   Updated: 2025/02/12 10:35:31 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_philo
{
	long	num;
	long	eating_count;
	long	last_eat;
	int		fork1;
	int		fork2;
}	t_philo;

typedef struct s_data
{
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	long			start_ts;
	pthread_mutex_t	*forks;
	int				*forks_states;
	pthread_mutex_t	printf_mutex;
	int				end;
}	t_data;

typedef struct s_newthread
{
	t_data	*data;
	int		current_num;
}	t_newthread;

// threads
void	*new_thread(void *data);

// actions
int		can_eat(t_philo *philo, t_data *data);
void	philo_sleep(t_philo *philo, t_data *data);
void	philo_eat(t_philo *philo, t_data *data);
void	philo_think(t_philo *philo, t_data *data);
void	die(t_philo *philo, t_data *data);

// forks
int		try_take_fork1(t_data *data, t_philo *philo, long ts);
int		try_take_fork2(t_data *data, t_philo *philo, long ts);

// utils
void	free_threads(pthread_t *threads, int allocated);
void	free_mutexs(t_data *data, int allocated);
long	get_time(struct timeval *timestamp);
void	print_msg(long num, long ms, pthread_mutex_t mutex, int msg);
long	ft_atol(const char *nptr);

#endif
