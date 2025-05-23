/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:03:39 by agruet            #+#    #+#             */
/*   Updated: 2025/05/05 12:24:08 by agruet           ###   ########.fr       */
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
}	t_data;

typedef struct s_monitor
{
	long	last_eat;
	sem_t	*death_sem;
	char	sem_name[5];
}	t_monitor;

typedef struct s_routine
{
	t_data		*data;
	t_philo		*philo;
	t_monitor	*monitor;
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
void	start_monitoring(t_routine *routine);

// actions
int		grab_forks(t_philo *philo, t_data *data, t_monitor *monitor);
int		philo_sleep(t_philo *philo, t_data *data);
int		philo_eat(t_philo *philo, t_data *data, t_monitor *monitor);
int		philo_think(t_philo *philo, t_data *data, t_monitor *monitor,
			bool first);
void	die(t_philo *philo, t_data *data, t_monitor *monitor);

// eating
void	is_finished(t_philo *philo, t_data *data);
void	release_forks(t_philo *philo, t_data *data);

// time
void	ft_usleep(size_t usec);
long	get_time(struct timeval *timestamp);
long	get_time_now(void);
long	get_sim_time(t_data *data);

// print_safe
void	print_safe(long timestamp, long id, char *message);

// utils
void	close_all(t_data *data, t_monitor *monitor);
void	exit_all(t_data *data);
void	kill_all(pid_t *pids, int amount);
void	wait_all(t_data *data, int amount);
long	get_time(struct timeval *timestamp);
void	print_msg(long num, t_data *data, int msg);
long	ft_atol(const char *nptr);
int		ft_pow(int nb, int power);

#endif
