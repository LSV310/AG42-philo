/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:04:23 by agruet            #+#    #+#             */
/*   Updated: 2025/02/12 11:29:11 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	can_eat(t_philo *philo, t_data *data)
{
	struct timeval	current_time;
	long			ts;

	gettimeofday(&current_time, NULL);
	ts = get_time(&current_time);
	if (!data->forks_states[philo->fork1] && !data->forks_states[philo->fork2])
	{
		if (pthread_mutex_lock(&data->forks[philo->fork1]))
			return (0);
		data->forks_states[philo->fork1] = 1;
		print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 0);
		if (pthread_mutex_lock(&data->forks[philo->fork2]))
		{
			pthread_mutex_unlock(&data->forks[philo->fork1]);
			data->forks_states[philo->fork1] = 0;
			return (0);
		}
		data->forks_states[philo->fork2] = 1;
		print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 0);
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo *philo, t_data *data)
{
	struct timeval	current_time;
	long			ts;

	if (data->end == 1)
		return ;
	gettimeofday(&current_time, NULL);
	ts = get_time(&current_time);
	if (philo->last_eat + data->time_to_die < ts + data->time_to_sleep)
		die(philo, data);
	else
	{
		print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 2);
		usleep(data->time_to_sleep * 1000);
		philo_think(philo, data);
	}
}

void	philo_eat(t_philo *philo, t_data *data)
{
	struct timeval	current_time;
	long			ts;

	if (data->end == 1)
		return ;
	gettimeofday(&current_time, NULL);
	ts = get_time(&current_time);
	if (philo->last_eat + data->time_to_die < ts + data->time_to_eat)
		die(philo, data);
	else
	{
		philo->last_eat = ts;
		print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 1);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(&data->forks[philo->fork1]);
		pthread_mutex_unlock(&data->forks[philo->fork2]);
		data->forks_states[philo->fork2] = 0;
		data->forks_states[philo->fork1] = 0;
		philo_sleep(philo, data);
	}
}

void	philo_think(t_philo *philo, t_data *data)
{
	struct timeval	current_time;
	long			ts;

	if (data->end == 1)
		return ;
	gettimeofday(&current_time, NULL);
	ts = get_time(&current_time);
	print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 3);
	while (!can_eat(philo, data))
	{
		if (data->end == 1)
			return ;
		gettimeofday(&current_time, NULL);
		ts = get_time(&current_time);
		if (ts > philo->last_eat + data->time_to_die)
		{
			die(philo, data);
			return ;
		}
		if (data->time_to_die >= 10)
			usleep(data->time_to_sleep * 1000 - 5);
		else
			usleep(8 * 1000);
	}
	philo_eat(philo, data);
}

void	die(t_philo *philo, t_data *data)
{
	struct timeval	current_time;
	long			ts;

	data->end = 1;
	usleep(data->time_to_die * 1000);
	gettimeofday(&current_time, NULL);
	ts = get_time(&current_time);
	print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 4);
}
