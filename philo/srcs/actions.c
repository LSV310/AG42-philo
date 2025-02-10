/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:04:23 by agruet            #+#    #+#             */
/*   Updated: 2025/02/10 13:52:34 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	can_eat()
{
	return (1);
}

void	philo_sleep(t_philo *philo, t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (philo->last_eat + data->time_to_die
		< get_time(&current_time) + data->time_to_sleep)
	{
		usleep(data->time_to_die * 1000);
		die(philo, data);
	}
	else
	{
		printf("%ld %ld is sleeping\n",
			get_time(&current_time) - data->simulation_start,
			philo->num);
		usleep(data->time_to_sleep * 1000);
		philo_think(philo, data);
	}
}

void	philo_eat(t_philo *philo, t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (philo->last_eat + data->time_to_die
		< get_time(&current_time) + data->time_to_eat)
	{
		usleep(data->time_to_die * 1000);
		die(philo, data);
	}
	else
	{
		philo->last_eat = get_time(&current_time);
		printf("%ld %ld is eating\n",
			get_time(&current_time) - data->simulation_start,
			philo->num);
		usleep(data->time_to_eat * 1000);
		philo_sleep(philo, data);
	}
}

void	philo_think(t_philo *philo, t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %ld is thinking\n",
			get_time(&current_time) - data->simulation_start,
			philo->num);
	while (!can_eat())
		usleep(100);
	philo_eat(philo, data);
}

void	die(t_philo *philo, t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %ld died\n",
			get_time(&current_time) - data->simulation_start,
			philo->num);
}
