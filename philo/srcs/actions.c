/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:04:23 by agruet            #+#    #+#             */
/*   Updated: 2025/02/21 12:45:10 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	can_eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->lock);
	if (data->end == true)
		return (pthread_mutex_unlock(&data->lock), 0);
	if (!data->forks_states[philo->fork1] && !data->forks_states[philo->fork2])
	{
		data->forks_states[philo->fork1] = 1;
		data->forks_states[philo->fork2] = 1;
		pthread_mutex_unlock(&data->lock);
		pthread_mutex_lock(&data->forks[philo->fork1]);
		pthread_mutex_lock(&data->forks[philo->fork2]);
		print_msg(philo->num, data, 0);
		print_msg(philo->num, data, 0);
		return (1);
	}
	pthread_mutex_unlock(&data->lock);
	return (0);
}

void	philo_sleep(t_philo *philo, t_data *data)
{
	long	ts;

	if (get_death(data) == true)
		return ;
	ts = get_time_now();
	print_msg(philo->num, data, 2);
	if (philo->last_eat + data->time_to_die < ts + data->time_to_sleep)
	{
		usleep((philo->last_eat + data->time_to_die - ts) * 1000);
		die(philo, data);
	}
	else
	{
		usleep(data->time_to_sleep * 1000);
		philo_think(philo, data, false);
	}
}

void	philo_eat(t_philo *philo, t_data *data)
{
	long	ts;

	if (get_death(data) == true)
	{
		release_forks(philo, data);
		return ;
	}
	ts = get_time_now();
	if (ts > philo->last_eat + data->time_to_die)
	{
		release_forks(philo, data);
		die(philo, data);
		return ;
	}
	philo->last_eat = get_time_now();
	print_msg(philo->num, data, 1);
	if (finished_eating(philo, data) == true)
	{
		usleep(data->time_to_eat * 1000);
		release_forks(philo, data);
		return ;
	}
	usleep(data->time_to_eat * 1000);
	release_forks(philo, data);
	philo_sleep(philo, data);
}

void	philo_think(t_philo *philo, t_data *data, bool first_think)
{
	if (get_death(data) == true)
		return ;
	print_msg(philo->num, data, 3);
	if (first_think == true)
		usleep(data->time_to_eat * 1000);
	else
		usleep(1000);
	if (get_death(data) == true)
		return ;
	while (!can_eat(philo, data))
	{
		usleep(10);
		if (get_death(data) == true)
			return ;
		if (get_time_now() > philo->last_eat + data->time_to_die)
		{
			die(philo, data);
			return ;
		}
	}
	philo_eat(philo, data);
}

void	die(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->lock);
	if (data->end == true)
	{
		pthread_mutex_unlock(&data->lock);
		return ;
	}
	data->end = true;
	pthread_mutex_unlock(&data->lock);
	print_msg(philo->num, data, 4);
}
