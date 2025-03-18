/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:12:28 by agruet            #+#    #+#             */
/*   Updated: 2025/03/18 17:14:31 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_monitoring(void *param)
{
	const t_routine	*routine_param = (t_routine *)param;
	const t_data	*data = routine_param->data;
	const t_philo	*philo = routine_param->philo;

	while (1)
	{
		if (get_time_now() > philo->last_eat + data->time_to_die)
			die((t_philo *)philo, (t_data *)data);
		usleep(100);
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

void	philo_start(t_data *data, t_philo *philo)
{
	pthread_t	thread1;
	pthread_t	thread2;
	t_routine	routine_param;

	philo->fork1 = false;
	philo->fork2 = false;
	routine_param.data = data;
	routine_param.philo = philo;
	if (pthread_create(&thread1, NULL, &death_monitoring, &routine_param))
		return ;
	if (pthread_detach(thread1))
		return ;
	if (pthread_create(&thread2, NULL, &death_monitoring, &routine_param))
		return ;
	if (pthread_detach(thread2))
		return ;
	if (philo->num % 2 == 1)
	{
		if (!can_eat(philo, data))
			philo_think(philo, data, false);
		else
			philo_eat(philo, data);
	}
	else
		philo_think(philo, data, true);
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
	if (data->number_of_philosophers == 1)
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
