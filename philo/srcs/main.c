/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:00:43 by agruet            #+#    #+#             */
/*   Updated: 2025/02/15 16:47:55 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		data->number_of_times_each_philosopher_must_eat = ft_atol(av[5]);
		if (data->number_of_times_each_philosopher_must_eat < 0)
		{
			printf("Invalid number of times each philosopher must eat\n");
			return (0);
		}
	}
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	return (1);
}

int	initialize_thread(t_data *data, pthread_t *threads, int i)
{
	t_newthread	*ini;

	ini = malloc(sizeof(t_newthread));
	if (!ini)
		return (0);
	ini->data = data;
	ini->current_num = i + 1;
	if (pthread_create(&threads[i], NULL, &new_thread, ini))
		return (0);
	return (1);
}

int	create_all_threads(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	data->threads_finished = false;
	data->threads_success = false;
	while (i < data->number_of_philosophers)
	{
		if (!initialize_thread(data, threads, i))
		{
			data->threads_finished = true;
			free_threads(threads, i);
			free_mutexs(data, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	data->start_ts = get_time_now();
	data->threads_success = true;
	data->threads_finished = true;
}

void	create_mutexs(t_data *data, int count)
{
	int	i;

	if (pthread_mutex_init(&data->states_mutex, NULL))
		exit(EXIT_FAILURE);
	if (pthread_mutex_init(&data->printf_mutex, NULL))
		(pthread_mutex_destroy(&data->states_mutex), exit(EXIT_FAILURE));
	if (pthread_mutex_init(&data->end_mutex, NULL))
		(pthread_mutex_destroy(&data->states_mutex),
			pthread_mutex_destroy(&data->printf_mutex), exit(EXIT_FAILURE));
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			free_mutexs(data, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	data->forks_states = malloc(sizeof(int) * count);
	if (!data->forks_states)
		(free_mutexs(data, count), exit(EXIT_FAILURE));
	while (i < count)
		data->forks_states[i++] = 0;
}

int	main(int ac, char **av)
{
	t_data			data;
	pthread_t		*threads;
	struct timeval	current_time;

	if (ac < 5)
		return (printf("Not enough arguments\n"), 1);
	if (ac > 6)
		return (printf("Too many arguments\n"), 1);
	if (!fill_data(ac, av, &data))
		return (EXIT_FAILURE);
	data.end = false;
	data.forks = malloc(sizeof(pthread_mutex_t) * data.number_of_philosophers);
	if (!data.forks)
		return (EXIT_FAILURE);
	create_mutexs(&data, data.number_of_philosophers);
	threads = malloc(sizeof(pthread_t) * data.number_of_philosophers);
	if (!threads)
		return (1);
	create_all_threads(&data, threads);
	free_threads(threads, data.number_of_philosophers);
	free_mutexs(&data, data.number_of_philosophers);
	return (EXIT_SUCCESS);
}
