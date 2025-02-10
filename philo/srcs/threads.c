/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:12:28 by agruet            #+#    #+#             */
/*   Updated: 2025/02/10 11:45:30 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*new_thread(void *arg)
{
	t_philo	philo;
	t_data	*data;

	philo.num = ((t_newthread *)arg)->current_num;
	data = ((t_newthread *)arg)->data;
	free(arg);
	philo.last_eat = data->simulation_start;
	philo.eating_count = 0;
	if (philo.num % 2 == 0)
		philo_eat(&philo, data);
	else
		philo_think(&philo, data);
	return (NULL);
}
