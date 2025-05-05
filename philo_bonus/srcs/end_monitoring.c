/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_monitoring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:18:59 by agruet            #+#    #+#             */
/*   Updated: 2025/05/05 12:24:23 by agruet           ###   ########.fr       */
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

void	*finish_monitoring(void *data)
{
	long	i;

	i = 0;
	ft_usleep(10000);
	while (i < ((t_data *)data)->number_of_philosophers)
	{
		sem_wait(((t_data *)data)->finish_sem);
		i++;
	}
	kill_all(((t_data *)data)->pids, ((t_data *)data)->number_of_philosophers);
	return (NULL);
}

void	wait_all(t_data *data, int amount)
{
	pthread_t	thread;
	int			status;

	if (pthread_create(&thread, NULL, &finish_monitoring, data))
		return ;
	pthread_detach(thread);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		kill_all(data->pids, data->number_of_philosophers);
	return ;
}
