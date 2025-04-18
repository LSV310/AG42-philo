/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:14:18 by agruet            #+#    #+#             */
/*   Updated: 2025/04/18 15:34:27 by agruet           ###   ########.fr       */
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
		if (get_time_now() > monitor->last_eat + data->time_to_die)
		{
			printf("%ld\n", monitor->last_eat);
			die((t_philo *)philo, (t_data *)data, (t_monitor *)monitor);
		}
		sem_post(monitor->death_sem);
		ft_usleep(10);
	}
}

void	*quit_monitoring(void *param)
{
	const t_routine	*routine_param = (t_routine *)param;
	const t_data	*data = routine_param->data;
	const t_philo	*philo = routine_param->philo;
	const t_monitor	*monitor = routine_param->monitor;

	sem_wait(data->quit_sem);
	close_all((t_data *)data, (t_monitor *)monitor);
	exit(EXIT_SUCCESS);
}

void	start_monitoring(t_routine *routine_param)
{
	pthread_t	thread1;
	pthread_t	thread2;

	if (pthread_create(&thread1, NULL, &death_monitoring, routine_param)
		|| pthread_detach(thread1)
		|| pthread_create(&thread2, NULL, &quit_monitoring, routine_param)
		|| pthread_detach(thread2))
		return ;
}
