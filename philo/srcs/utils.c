/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:51 by agruet            #+#    #+#             */
/*   Updated: 2025/02/19 18:06:52 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_threads(pthread_t *threads, int allocated)
{
	int	i;

	i = 0;
	while (i < allocated)
		pthread_join(threads[i++], NULL);
	free(threads);
}

void	free_mutexs(t_data *data, int allocated)
{
	int	i;

	i = 0;
	while (i < allocated)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->printf_mutex);
	pthread_mutex_destroy(&data->states_mutex);
	free(data->forks);
}

bool	get_death(t_data *data)
{
	bool	end;

	end = false;
	if (pthread_mutex_lock(&data->end_mutex))
		return (true);
	if (data->end == true)
		end = true;
	pthread_mutex_unlock(&data->end_mutex);
	return (end);
}

void	print_msg(long num, t_data *data, int msg)
{
	long	ms;

	if (pthread_mutex_lock(&data->printf_mutex))
		return ;
	ms = get_sim_time(data);
	if (msg == 0)
		printf("%ld %ld has taken a fork\n", ms, num);
	else if (msg == 1)
		printf("%ld %ld is eating\n", ms, num);
	else if (msg == 2)
		printf("%ld %ld is sleeping\n", ms, num);
	else if (msg == 3)
		printf("%ld %ld is thinking\n", ms, num);
	else if (msg == 4)
		printf("%ld %ld died\n", ms, num);
	pthread_mutex_unlock(&data->printf_mutex);
}

long	ft_atol(const char *nptr)
{
	int		i;
	int		j;
	size_t	result;

	i = 0;
	result = 0;
	while (nptr[i] == '0')
		i++;
	j = i;
	while (nptr[i] >= '0' && nptr[i] <= '9' && i - j < 19)
	{
		result = result * 10 + (nptr[i++] - '0');
		if (result > LONG_MAX)
			return (-1);
	}
	if (nptr[i] != '\0')
		return (-1);
	return (result);
}
