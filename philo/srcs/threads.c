/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:12:28 by agruet            #+#    #+#             */
/*   Updated: 2025/02/18 12:22:49 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	attribute_forks(t_data *data, t_philo *philo)
{
	philo->fork1 = philo->num - 1;
	if (philo->num == data->number_of_philosophers)
		philo->fork2 = 0;
	else
		philo->fork2 = philo->num;
	if (philo->fork1 == philo->fork2)
		return (0);
	return (1);
}

int	all_threads_created(t_data *data, t_philo *philo)
{
	while (data->threads_finished == false)
		usleep(10);
	if (data->threads_success == false)
		return (0);
	return (1);
}

void	philo_start(t_data *data, t_philo *philo)
{
	if (philo->num % 2 == 1)
	{
		while (!can_eat(philo, data))
			usleep(10);
		philo_eat(philo, data);
	}
	else
		philo_think(philo, data, true);
}

void	*new_thread(void *arg)
{
	t_philo	philo;
	t_data	*data;

	philo.num = ((t_newthread *)arg)->current_num;
	data = ((t_newthread *)arg)->data;
	free(arg);
	philo.eating_count = 0;
	if (!all_threads_created(data, &philo))
		return (NULL);
	philo.last_eat = data->start_ts;
	if (!attribute_forks(data, &philo))
	{
		usleep(data->time_to_die * 1000);
		die(&philo, data);
		return (NULL);
	}
	philo_start(data, &philo);
	return (NULL);
}
