/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:00:43 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 14:04:25 by agruet           ###   ########.fr       */
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

pid_t	*create_all_processes(t_data *data)
{
	int	i;

	data->pids = malloc(sizeof(pid_t) * (data->number_of_philosophers + 1));
	if (!data->pids)
		return (NULL);
	memset(data->pids, 0, data->number_of_philosophers * sizeof(pid_t));
	i = 0;
	data->start_ts = get_time_now();
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

int	create_sems(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/finished");
	sem_unlink("/quit");
	data->fork_sem = sem_open("/forks", O_CREAT, 0644, data->number_of_philosophers);
	if (data->fork_sem == SEM_FAILED)
		return (EXIT_FAILURE);
	data->finish_sem = sem_open("/finished", O_CREAT, 0644, 0);
	if (data->finish_sem == SEM_FAILED)
		return (exit_all(data), EXIT_FAILURE);
	sem_post(data->finish_sem);
	sem_wait(data->finish_sem);
	data->quit_sem = sem_open("/quit", O_CREAT, 0644, 0);
	if (data->quit_sem == SEM_FAILED)
		return (exit_all(data), EXIT_FAILURE);
	sem_post(data->quit_sem);
	sem_wait(data->quit_sem);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	struct timeval	current_time;

	if (ac < 5)
		return (printf("Not enough arguments\n"), 1);
	if (ac > 6)
		return (printf("Too many arguments\n"), 1);
	if (!fill_data(ac, av, &data))
		return (EXIT_FAILURE);
	data.pids = NULL;
	if (create_sems(&data))
		return (EXIT_FAILURE);
	if (!create_all_processes(&data))
		return (exit_all(&data), EXIT_FAILURE);
	wait_all(&data, data.number_of_philosophers);
	exit_all(&data);
	return (EXIT_SUCCESS);
}
