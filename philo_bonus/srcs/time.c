/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:08:29 by agruet            #+#    #+#             */
/*   Updated: 2025/05/05 15:16:39 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usleep(size_t usec)
{
	long	start;

	start = get_time_now() + usec / 1000;
	while (get_time_now() < start)
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
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (get_time(&timestamp));
}

long	get_sim_time(t_data *data)
{
	return (get_time_now() - data->start_ts);
}
