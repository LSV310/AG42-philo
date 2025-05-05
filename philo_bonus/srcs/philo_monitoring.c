/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:14:18 by agruet            #+#    #+#             */
/*   Updated: 2025/05/05 14:36:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_monitoring(void *param)
{
	const t_routine	*routine_param = (t_routine *)param;
	t_data			*data;
	t_philo			*philo;
	t_monitor		*monitor;

	data = routine_param->data;
	philo = routine_param->philo;
	monitor = routine_param->monitor;
	while (1)
	{
		sem_wait(monitor->death_sem);
		usleep(10);
		if (get_time_now() > monitor->last_eat + data->time_to_die)
			die((t_philo *)philo, (t_data *)data, (t_monitor *)monitor);
		sem_post(monitor->death_sem);
		usleep(10);
	}
}

void	start_monitoring(t_routine *routine_param)
{
	pthread_t	thread1;

	if (pthread_create(&thread1, NULL, &death_monitoring, routine_param))
		return ;
	pthread_detach(thread1);
}
