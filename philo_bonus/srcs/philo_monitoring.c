/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:14:18 by agruet            #+#    #+#             */
/*   Updated: 2025/04/16 13:10:10 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_monitoring(void *param)
{
	const t_routine	*routine_param = (t_routine *)param;
	t_data			*data;
	t_philo			*philo;

	data = routine_param->data;
	philo = routine_param->philo;
	while (1)
	{
		if (get_time_now() > philo->last_eat + data->time_to_die)
			die((t_philo *)philo, (t_data *)data);
		ft_usleep(10);
	}
}

void	*quit_monitoring(void *param)
{
	const t_routine	*routine_param = (t_routine *)param;
	const t_data	*data = routine_param->data;
	const t_philo	*philo = routine_param->philo;

	sem_wait(data->quit_sem);
	sem_close(data->fork_sem);
	sem_close(data->finish_sem);
	sem_close(data->quit_sem);
	exit(EXIT_SUCCESS);
}

void	start_monitoring(t_data *data, t_philo *philo)
{
	pthread_t	thread1;
	pthread_t	thread2;
	t_routine	routine_param;

	routine_param.data = data;
	routine_param.philo = philo;
	printf("%p\n", data->quit_sem);
	if (pthread_create(&thread1, NULL, &death_monitoring, &routine_param)
		|| pthread_detach(thread1)
		|| pthread_create(&thread2, NULL, &quit_monitoring, &routine_param)
		|| pthread_detach(thread2))
		return ;
}
