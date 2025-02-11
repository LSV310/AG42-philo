/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:12:28 by agruet            #+#    #+#             */
/*   Updated: 2025/02/11 16:24:13 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	attribute_forks(t_data *data, t_philo *philo)
{
	philo->fork1 = philo->num - 1;
	if (philo->num == data->number_of_philosophers)
		philo->fork2 = 0;
	else
		philo->fork2 = philo->num;
}

void	*new_thread(void *arg)
{
	t_philo	philo;
	t_data	*data;

	philo.num = ((t_newthread *)arg)->current_num;
	data = ((t_newthread *)arg)->data;
	free(arg);
	philo.last_eat = data->start_ts;
	philo.eating_count = 0;
	attribute_forks(data, &philo);
	if (philo.num % 2 == 0)
	{
		while (!can_eat(&philo, data))
			usleep(5 * 1000);
		philo_eat(&philo, data);
	}
	else
		philo_think(&philo, data);
	return (NULL);
}
