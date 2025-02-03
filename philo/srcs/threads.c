/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:12:28 by agruet            #+#    #+#             */
/*   Updated: 2025/02/03 17:22:42 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*new_thread(void *arg)
{
	t_philo	philo;
	t_data	*data;

	data = (t_data *)arg;
	philo_sleep(data->time_to_sleep);
	philo.eating_count = 0;
	return (NULL);
}
