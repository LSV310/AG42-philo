/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:03:39 by agruet            #+#    #+#             */
/*   Updated: 2025/02/21 12:22:09 by agruet           ###   ########.fr       */
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
# include <stdbool.h>
# include <errno.h>

typedef struct s_philo
{
	long	num;
	long	eating_count;
	long	last_eat;
	int		fork1;
	int		fork2;
	bool	finished_eating;
}	t_philo;

typedef struct s_data
{
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			times_must_eat;
	long			start_ts;
	int				*forks_states;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	int				finished_amount;
	bool			end;
	bool			threads_success;
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
void	philo_think(t_philo *philo, t_data *data, bool first_think);
void	die(t_philo *philo, t_data *data);

// eating
bool	finished_eating(t_philo *philo, t_data *data);
void	release_forks(t_philo *philo, t_data *data);

// time
long	get_time(struct timeval *timestamp);
long	get_time_now(void);
long	get_sim_time(t_data *data);

// utils
void	free_threads(pthread_t *threads, int allocated);
void	free_mutexs(t_data *data, int allocated);
bool	get_death(t_data *data);
long	get_time(struct timeval *timestamp);
void	print_msg(long num, t_data *data, int msg);
long	ft_atol(const char *nptr);

#endif
