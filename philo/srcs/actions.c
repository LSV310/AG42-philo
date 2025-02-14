/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:04:23 by agruet            #+#    #+#             */
/*   Updated: 2025/02/14 16:31:11 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	can_eat(t_philo *philo, t_data *data)
{
	if (data->end == 1)
		return (0);
	if (pthread_mutex_lock(&data->states_mutex))
		return (0);
	if (!data->forks_states[philo->fork1] && !data->forks_states[philo->fork2])
	{
		if (!lock_fork1(philo, data))
			return (0);
		if (!lock_fork2(philo, data))
			return (0);
		pthread_mutex_unlock(&data->states_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->states_mutex);
	return (0);
}

void	philo_sleep(t_philo *philo, t_data *data)
{
	long	ts;

	if (data->end == 1)
		return ;
	ts = get_time_now();
	if (philo->last_eat + data->time_to_die < ts + data->time_to_sleep)
	{
		usleep(data->time_to_die);
		die(philo, data);
	}
	else
	{
		print_msg(philo->num, data, 2);
		usleep(data->time_to_sleep * 1000);
		philo_think(philo, data);
	}
}

void	philo_eat(t_philo *philo, t_data *data)
{
	if (data->end == 1)
		return ;
	if (get_time_now() > philo->last_eat + data->time_to_die)
	{
		die(philo, data);
		return ;
	}
	philo->last_eat = get_time_now();
	print_msg(philo->num, data, 1);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[philo->fork1]);
	pthread_mutex_unlock(&data->forks[philo->fork2]);
	if (pthread_mutex_lock(&data->states_mutex))
		return ;
	data->forks_states[philo->fork1] = 0;
	data->forks_states[philo->fork2] = 0;
	pthread_mutex_unlock(&data->states_mutex);
	philo_sleep(philo, data);
}

void	philo_think(t_philo *philo, t_data *data)
{
	if (data->end == 1)
		return ;
	print_msg(philo->num, data, 3);
	usleep(50);
	while (!can_eat(philo, data))
	{
		if (data->end == 1)
			return ;
		if (get_time_now() > philo->last_eat + data->time_to_die)
		{
			die(philo, data);
			return ;
		}
		usleep(50);
	}
	philo_eat(philo, data);
}

void	die(t_philo *philo, t_data *data)
{
	data->end = 1;
	print_msg(philo->num, data, 4);
}
