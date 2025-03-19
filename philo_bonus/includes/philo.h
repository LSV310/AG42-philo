/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:03:39 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 00:17:24 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <signal.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philo
{
	long	num;
	long	eating_count;
	long	last_eat;
	bool	fork1;
	bool	fork2;
	bool	finished_eating;
}	t_philo;

typedef struct s_data
{
	long	number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	times_must_eat;
	long	start_ts;
	pid_t	*pids;
	sem_t	*fork_sem;
	sem_t	*finish_sem;
	sem_t	*quit_sem;
}	t_data;

typedef struct	s_routine
{
	t_data	*data;
	t_philo	*philo;
}	t_routine;

typedef enum ACTIONS
{
	DYING,
	EATING,
	SLEEPING,
	THINKING
}	t_action;

// processes
void	*new_process(t_data *data, int nb);
void	start_monitoring(t_data *data, t_philo *philo);

// actions
int		can_eat(t_philo *philo, t_data *data);
int		philo_sleep(t_philo *philo, t_data *data);
int		philo_eat(t_philo *philo, t_data *data);
int		philo_think(t_philo *philo, t_data *data, bool first_think);
void	die(t_philo *philo, t_data *data);

// eating
void	is_finished(t_philo *philo, t_data *data);
void	release_forks(t_philo *philo, t_data *data);

// time
long	get_time(struct timeval *timestamp);
long	get_time_now(void);
long	get_sim_time(t_data *data);

// print_safe
void	print_safe(long timestamp, long id, char *message);

// utils
void	exit_all(t_data *data);
void	kill_all(pid_t *pids, int amount);
void	quit_all(t_data *data);
void	wait_all(t_data *data, int amount);
long	get_time(struct timeval *timestamp);
void	print_msg(long num, t_data *data, int msg);
long	ft_atol(const char *nptr);

#endif
