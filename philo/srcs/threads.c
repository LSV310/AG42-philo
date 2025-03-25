/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:12:28 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 13:39:23 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	all_threads_created(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->lock);
	if (data->threads_success == false)
	{
		pthread_mutex_unlock(&data->lock);
		return (0);
	}
	pthread_mutex_unlock(&data->lock);
	return (1);
}

void	attribute_forks(t_data *data, t_philo *philo)
{
	if (philo->num % 2 == 1)
	{
		if (philo->num == data->number_of_philosophers)
			philo->fork1 = 0;
		else
			philo->fork1 = philo->num;
		philo->fork2 = philo->num - 1;
	}
	else
	{
		philo->fork1 = philo->num - 1;
		if (philo->num == data->number_of_philosophers)
			philo->fork2 = 0;
		else
			philo->fork2 = philo->num;
	}
}

static t_action	first_action(t_data *data, t_philo *philo)
{
	if (philo->num % 2 == 1)
	{
		if (!can_eat(philo, data))
			philo_think(philo, data, false);
		philo_eat(philo, data);
		return (EATING);
	}
	else
	{
		philo_think(philo, data, true);
		return (THINKING);
	}
}

void	philo_start(t_data *data, t_philo *philo)
{
	t_action	action;

	action = first_action(data, philo);
	if (action == DYING)
		return ;
	while (true)
	{
		action++;
		if (action > THINKING)
			action = EATING;
		if (action == EATING && philo_eat(philo, data))
			return ;
		else if (action == SLEEPING && philo_sleep(philo, data))
			return ;
		else if (action == THINKING && philo_think(philo, data, false))
			return ;
	}
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
	philo.finished_eating = false;
	if (data->times_must_eat == 0)
		return (NULL);
	attribute_forks(data, &philo);
	if (data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&data->forks[philo.fork1]);
		print_msg(philo.num, data, 0);
		usleep(data->time_to_die * 1000);
		pthread_mutex_unlock(&data->forks[philo.fork1]);
		die(&philo, data);
		return (NULL);
	}
	philo_start(data, &philo);
	return (NULL);
}
