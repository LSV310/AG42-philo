/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:20:51 by agruet            #+#    #+#             */
/*   Updated: 2025/02/19 17:59:42 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_fork1(t_philo *philo, t_data *data)
{
	data->forks_states[philo->fork1] = 1;
	if (pthread_mutex_lock(&data->forks[philo->fork1]))
	{
		data->forks_states[philo->fork1] = 0;
		pthread_mutex_unlock(&data->states_mutex);
		return (0);
	}
	print_msg(philo->num, data, 0);
	return (1);
}

int	lock_fork2(t_philo *philo, t_data *data)
{
	data->forks_states[philo->fork2] = 1;
	if (pthread_mutex_lock(&data->forks[philo->fork2]))
	{
		pthread_mutex_unlock(&data->forks[philo->fork1]);
		data->forks_states[philo->fork1] = 0;
		data->forks_states[philo->fork2] = 0;
		pthread_mutex_unlock(&data->states_mutex);
		return (0);
	}
	print_msg(philo->num, data, 0);
	return (1);
}

void	release_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&data->forks[philo->fork1]);
	pthread_mutex_unlock(&data->forks[philo->fork2]);
	if (pthread_mutex_lock(&data->states_mutex))
		return ;
	data->forks_states[philo->fork1] = 0;
	data->forks_states[philo->fork2] = 0;
	pthread_mutex_unlock(&data->states_mutex);
}
