/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:08:29 by agruet            #+#    #+#             */
/*   Updated: 2025/04/16 13:10:32 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t usec)
{
	long	start;

	start = get_time_now();
	while (get_time_now() < start + usec / 1000)
		usleep(10);
}

long	get_time(struct timeval *timestamp)
{
	long	time;

	time = timestamp->tv_sec * 1000 + timestamp->tv_usec / 1000;
	return (time);
}

long	get_time_now(void)
{
	long			time;
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (get_time(&timestamp));
}

long	get_sim_time(t_data *data)
{
	return (get_time_now() - data->start_ts);
}
