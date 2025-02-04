/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:03:39 by agruet            #+#    #+#             */
/*   Updated: 2025/02/04 15:55:27 by agruet           ###   ########.fr       */
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

typedef struct s_philo
{
	long			num;
	long			eating_count;
	long			last_eat;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_data
{
	long	number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	number_of_times_each_philosopher_must_eat;
	long	simulation_start;
}	t_data;

typedef struct s_newthread
{
	t_data	*data;
	int		current_num;
}	t_newthread;

// threads
void	*new_thread(void *data);

// actions
void	philo_sleep(t_philo *philo, t_data *data);
void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);
void	die(t_philo *philo);

// utils
void	free_all(t_data *data, pthread_t *threads, int allocated);
long	get_time(struct timeval *timestamp);
long	ft_atol(const char *nptr);

#endif
