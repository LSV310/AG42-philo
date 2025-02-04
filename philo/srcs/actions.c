/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:04:23 by agruet            #+#    #+#             */
/*   Updated: 2025/02/04 16:12:05 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo, t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (philo->last_eat + data->time_to_die
		< get_time(&current_time) + data->time_to_sleep)
	{
		usleep(data->time_to_die * 1000);
		die(philo);
	}
	else
	{
		printf("%ld %ld is sleeping\n",
			get_time(&current_time) - data->simulation_start,
			philo->num);
		usleep(data->time_to_sleep * 1000);
	}
}

void	philo_eat(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	(void)philo;
}

void	philo_think(t_philo *philo)
{
	(void)philo;
}

void	die(t_philo *philo)
{
	(void)philo;
}
