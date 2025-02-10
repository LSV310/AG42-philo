/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:51 by agruet            #+#    #+#             */
/*   Updated: 2025/02/10 13:43:01 by agruet           ###   ########.fr       */
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

void	free_mutexs(pthread_mutex_t *forks, int allocated)
{
	int	i;

	i = 1;
	while (i < allocated + 1)
		pthread_mutex_destroy(&forks[i++]);
	free(forks);
}

long	get_time(struct timeval *timestamp)
{
	long	time;

	time = timestamp->tv_sec * 1000 + timestamp->tv_usec / 1000;
	return (time);
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
