/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:03:39 by agruet            #+#    #+#             */
/*   Updated: 2025/02/03 17:29:16 by agruet           ###   ########.fr       */
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
	long				num;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				eating_count;
	pthread_mutex_t		fork;
}	t_philo;

typedef struct s_data
{
	long	number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	number_of_times_each_philosopher_must_eat;
}	t_data;

// threads
void	*new_thread(void *data);

// actions
void	philo_sleep(long time_to_sleep);

// utils
void	free_all(t_data *data, pthread_t *threads);
long	ft_atol(const char *nptr);

#endif
