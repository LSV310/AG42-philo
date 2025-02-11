/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:04:23 by agruet            #+#    #+#             */
/*   Updated: 2025/02/11 16:23:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	can_eat(t_philo *philo, t_data *data)
{
	static int		fork1;
	static int		fork2;
	struct timeval	current_time;
	long			ts;

	gettimeofday(&current_time, NULL);
	ts = get_time(&current_time);
	if (!fork1)
		fork1 = try_take_fork1(data, philo, ts);
	if (fork1 == 2)
		return (0);
	if (!fork2)
		fork2 = try_take_fork2(data, philo, ts);
	if (fork2 == 2)
		return (0);
	/* if (fork1)
	{
		pthread_mutex_lock(&data->printf_mutex);
		printf("%ld have fork %d\n", philo->num, philo->fork1 + 1);
		pthread_mutex_unlock(&data->printf_mutex);
	}
	if (fork2)
	{
		pthread_mutex_lock(&data->printf_mutex);
		printf("%ld have fork %d\n", philo->num, philo->fork2 + 1);
		pthread_mutex_unlock(&data->printf_mutex);
	} */
	if (fork1 && fork2)
	{
		fork1 = 0;
		fork2 = 0;
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo *philo, t_data *data)
{
	struct timeval	current_time;
	long			ts;

	gettimeofday(&current_time, NULL);
	ts = get_time(&current_time);
	if (philo->last_eat + data->time_to_die < ts + data->time_to_sleep)
	{
		usleep(data->time_to_die * 1000);
		die(philo, data);
	}
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

	gettimeofday(&current_time, NULL);
	ts = get_time(&current_time);
	if (philo->last_eat + data->time_to_die < ts + data->time_to_eat)
	{
		usleep(data->time_to_die * 1000);
		die(philo, data);
	}
	else
	{
		philo->last_eat = ts;
		print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 1);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_lock(&data->printf_mutex);
		printf("%ld %ld has RELEASED fork %d\n", get_time(&current_time) - data->start_ts, philo->num, philo->fork1 + 1);
		printf("%ld %ld has RELEASED fork %d\n", get_time(&current_time) - data->start_ts, philo->num, philo->fork2 + 1);
		pthread_mutex_unlock(&data->printf_mutex);
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

	gettimeofday(&current_time, NULL);
	ts = get_time(&current_time);
	print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 3);
	while (!can_eat(philo, data))
	{
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

	gettimeofday(&current_time, NULL);
	ts = get_time(&current_time);
	print_msg(philo->num, ts - data->start_ts, data->printf_mutex, 4);
}
