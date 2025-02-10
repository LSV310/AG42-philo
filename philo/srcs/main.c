/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:00:43 by agruet            #+#    #+#             */
/*   Updated: 2025/02/10 18:27:46 by agruet           ###   ########.fr       */
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

void	create_mutexs(t_data *data, int count)
{
	int	i;

	if (count == 0)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * (count + 2));
	if (!data->forks)
		exit(1);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&data->forks[i + 1], NULL))
		{
			free_mutexs(data->forks, i);
			exit(1);
		}
		i++;
	}
	data->forks[i] = data->forks[1];
	data->forks[0] = data->forks[i - 1];
}

int	main(int ac, char **av)
{
	t_data			data;
	pthread_t		*threads;
	struct timeval	current_time;
	int				i;

	if (ac < 5)
		return (printf("Not enough arguments\n"), 1);
	if (ac > 6)
		return (printf("Too many arguments\n"), 1);
	if (!fill_data(ac, av, &data))
		return (1);
	create_mutexs(&data, data.number_of_philosophers);
	threads = malloc(sizeof(pthread_t) * data.number_of_philosophers);
	if (!threads)
		return (1);
	i = 0;
	gettimeofday(&current_time, NULL);
	data.simulation_start = get_time(&current_time);
	while (i < data.number_of_philosophers)
	{
		if (!initialize_thread(&data, threads, i++))
			return (free_mutexs(data.forks, i), free_threads(threads, i), 1);
	}
	(free_mutexs(data.forks, i), free_threads(threads, i));
	return (0);
}
