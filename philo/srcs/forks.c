/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:20:51 by agruet            #+#    #+#             */
/*   Updated: 2025/02/12 11:09:11 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* int	try_take_fork1(t_data *data, t_philo *philo, long ts)
{
	int	fork1;

	if (!data->forks_states[philo->fork1])
	{
		fork1 = pthread_mutex_lock(&data->forks[philo->fork1]);
		if (fork1)
			return (2);
		data->forks_states[philo->fork1] = 1;
		// print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 0);
		printf("%ld %ld has TAKEN fork %d\n", ts - data->start_ts, philo->num, philo->fork1 + 1);
		return (1);
	}
	return (0);
}

int	try_take_fork2(t_data *data, t_philo *philo, long ts)
{
	int	fork2;

	if (!data->forks_states[philo->fork2])
	{
		fork2 = pthread_mutex_lock(&data->forks[philo->fork2]);
		if (fork2)
			return (2);
		data->forks_states[philo->fork2] = 1;
		// print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 0);
		printf("%ld %ld has TAKEN fork %d\n", ts - data->start_ts, philo->num, philo->fork2 + 1);
		return (1);
	}
	return (0);
} */
