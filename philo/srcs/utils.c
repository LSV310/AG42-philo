/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:51 by agruet            #+#    #+#             */
/*   Updated: 2025/02/11 15:17:44 by agruet           ###   ########.fr       */
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
	pthread_mutex_destroy(&data->printf_mutex);
	free(data->forks);
	free(data->forks_states);
}

long	get_time(struct timeval *timestamp)
{
	long	time;

	time = timestamp->tv_sec * 1000 + timestamp->tv_usec / 1000;
	return (time);
}

void	print_msg(long num, long ms, pthread_mutex_t mutex, int msg)
{
	if (pthread_mutex_lock(&mutex))
		return ;
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
	pthread_mutex_unlock(&mutex);
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
