/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:20:51 by agruet            #+#    #+#             */
/*   Updated: 2025/04/16 13:04:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	finished_eating(t_philo *philo, t_data *data)
{
	philo->eating_count++;
	pthread_mutex_lock(&data->lock);
	if (data->end == true)
	{
		pthread_mutex_unlock(&data->lock);
		return (true);
	}
	if (data->times_must_eat != -1 && philo->finished_eating == false
		&& philo->eating_count >= data->times_must_eat)
	{
		philo->finished_eating = true;
		data->finished_amount++;
	}
	if (data->finished_amount >= data->number_of_philosophers)
	{
		data->end = true;
		pthread_mutex_unlock(&data->lock);
		return (true);
	}
	pthread_mutex_unlock(&data->lock);
	return (false);
}

void	eat_usleep(t_philo *philo, t_data *data)
{
	if (data->time_to_die < data->time_to_eat)
		ft_usleep(data->time_to_die * 1000);
	else
		ft_usleep(data->time_to_eat * 1000);
}

void	release_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&data->forks[philo->fork1]);
	pthread_mutex_unlock(&data->forks[philo->fork2]);
	pthread_mutex_lock(&data->lock);
	data->forks_states[philo->fork1] = 0;
	data->forks_states[philo->fork2] = 0;
	pthread_mutex_unlock(&data->lock);
}
