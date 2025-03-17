/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:00:43 by agruet            #+#    #+#             */
/*   Updated: 2025/03/17 17:07:47 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	fill_data(int ac, char **av, t_data *data)
{
	data->number_of_philosophers = ft_atol(av[1]);
	if (data->number_of_philosophers <= 0)
		return (printf("Invalid number of philosophers\n"), 0);
	data->time_to_die = ft_atol(av[2]);
	if (data->time_to_die < 0)
		return (printf("Invalid time to die\n"), 0);
	data->time_to_eat = ft_atol(av[3]);
	if (data->time_to_eat < 0)
		return (printf("Invalid time to eat\n"), 0);
	data->time_to_sleep = ft_atol(av[4]);
	if (data->time_to_sleep < 0)
		return (printf("Invalid time to sleep\n"), 0);
	if (ac == 6)
	{
		data->times_must_eat = ft_atol(av[5]);
		if (data->times_must_eat < 0)
		{
			printf("Invalid number of times each philosopher must eat\n");
			return (0);
		}
	}
	else
		data->times_must_eat = -1;
	return (1);
}

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

pid_t	*create_all_processes(t_data *data)
{
	int	i;

	data->pids = malloc(sizeof(pid_t) * (data->number_of_philosophers + 1));
	if(!data->pids)
		return (NULL);
	memset(data->pids, 0, data->number_of_philosophers * sizeof(pid_t));
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
		{
			kill_all(data->pids, i);
			free(data->pids);
			return (NULL);
		}
		else if (data->pids[i] == 0)
			new_process(data, i);
		i++;
	}
	data->pids[i] = 0;
	return (data->pids);
}

void	rm_semaphore(sem_t *sem)
{
	sem_close(sem);
	sem_unlink("/forks");
}

int	wait_all(t_data *data, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount && data->pids[i])
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill_all(data->pids, amount);
				return (1);
			}
			else
				data->finished_amount++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	struct timeval	current_time;
	sem_t			*sem;

	if (ac < 5)
		return (printf("Not enough arguments\n"), 1);
	if (ac > 6)
		return (printf("Too many arguments\n"), 1);
	if (!fill_data(ac, av, &data))
		return (EXIT_FAILURE);
	data.end = false;
	data.finished_amount = 0;
	sem = sem_open("/forks", O_CREAT, 0644, data.number_of_philosophers);
	if (sem == SEM_FAILED)
		return (EXIT_FAILURE);
	if (!create_all_processes(&data))
		return (rm_semaphore(sem), EXIT_FAILURE);
	if (wait_all(&data, data.number_of_philosophers)
		|| data.finished_amount != data.number_of_philosophers)
		return (free(data.pids), EXIT_FAILURE);
	free(data.pids);
	return (EXIT_SUCCESS);
}
