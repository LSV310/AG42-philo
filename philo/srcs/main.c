/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:00:43 by agruet            #+#    #+#             */
/*   Updated: 2025/02/03 17:10:25 by agruet           ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	*threads;
	int			i;

	if (ac < 5)
		return (printf("Not enough arguments\n"), 1);
	if (ac > 6)
		return (printf("Too many arguments\n"), 1);
	if (!fill_data(ac, av, &data))
		return (1);
	threads = malloc(sizeof(pthread_t) * data.number_of_philosophers);
	if (!threads)
		return (1);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_create(&threads[i], NULL, &new_thread, &data);
		i++;
	}
	free_all(&data, threads);
	return (0);
}
