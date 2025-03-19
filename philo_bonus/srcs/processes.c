/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:12:28 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 00:15:35 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_action	first_action(t_data *data, t_philo *philo)
{
	if (philo->num % 2 == 1)
	{
		while (!can_eat(philo, data))
		{
			if (get_time_now() > philo->last_eat + data->time_to_die)
			{
				die(philo, data);
				return (DYING);
			}
			usleep(10);
		}
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

	philo->fork1 = false;
	philo->fork2 = false;
	start_monitoring(data, philo);
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

void	*new_process(t_data *data, int nb)
{
	t_philo	philo;

	free(data->pids);
	philo.num = nb;
	philo.eating_count = 0;
	philo.finished_eating = false;
	philo.last_eat = data->start_ts;
	if (data->times_must_eat == 0)
		exit(EXIT_SUCCESS);
	if (data->number_of_philosophers == 1) // REMOVE THIS IF I'M GOOD
	{
		print_msg(philo.num, data, 0);
		usleep(data->time_to_die * 1000);
		die(&philo, data);
		exit(EXIT_SUCCESS);
	}
	philo_start(data, &philo);
	exit(EXIT_FAILURE);
	return (NULL);
}
