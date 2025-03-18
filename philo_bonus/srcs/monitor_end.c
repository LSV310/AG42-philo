/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:18:59 by agruet            #+#    #+#             */
/*   Updated: 2025/03/18 17:21:18 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	quit_all(pid_t *pids, int amount)
{
	int	i;

	if (!pids)
		return ;
	i = 0;
	while (i < amount && pids[i])
	{
		kill(pids[i], SIGTERM);
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
	return (NULL);
}

void	wait_all(t_data *data, int amount)
{
	int			i;
	pthread_t	thread;

	if (pthread_create(&thread, NULL, &finish_monitoring, data))
	{
		kill_all(data->pids, data->number_of_philosophers);
		return ;
	}
	if (pthread_detach(thread))
	{
		kill_all(data->pids, data->number_of_philosophers);
		return ;
	}
	while (i < data->number_of_philosophers)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	return ;
}
