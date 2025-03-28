/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_monitoring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:18:59 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 13:58:08 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	kill_all(pid_t *pids, int amount)
{
	int	i;

	if (!pids)
		return ;
	i = 0;
	while (i < amount && pids[i])
	{
		kill(pids[i], SIGKILL);
		i++;
	}
}

void	quit_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		sem_post(data->quit_sem);
		i++;
	}
}

void	*finish_monitoring(void *data)
{
	long	i;

	i = 0;
	while (i < ((t_data *)data)->number_of_philosophers)
	{
		sem_wait(((t_data *)data)->finish_sem);
		i++;
	}
	quit_all(data);
	return (NULL);
}

void	wait_all(t_data *data, int amount)
{
	int			i;
	int			status;
	pthread_t	thread;

	if (pthread_create(&thread, NULL, &finish_monitoring, data))
		return ;
	pthread_detach(thread);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		quit_all(data);
		i++;
	}
	return ;
}
