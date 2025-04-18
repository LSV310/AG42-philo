/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:51 by agruet            #+#    #+#             */
/*   Updated: 2025/04/18 19:15:11 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	close_all(t_data *data, t_monitor *monitor)
{
	sem_t	*sem;

	sem_close(data->fork_sem);
	sem_close(data->finish_sem);
	sem_close(data->quit_sem);
	if (monitor->death_sem)
	{
		sem = monitor->death_sem;
		monitor->death_sem = NULL;
		sem_close(sem);
		sem_unlink(monitor->sem_name);
	}
}

void	exit_all(t_data *data)
{
	if (data->pids)
		free(data->pids);
	if (!data->fork_sem)
		return ;
	sem_close(data->fork_sem);
	sem_unlink("/forks");
	if (!data->finish_sem)
		return ;
	sem_close(data->finish_sem);
	sem_unlink("/finished");
	if (!data->quit_sem)
		return ;
	sem_close(data->quit_sem);
	sem_unlink("/quit");
}

void	print_msg(long num, t_data *data, int msg)
{
	long	ms;

	ms = get_sim_time(data);
	if (msg == 0)
		print_safe(ms, num, "has taken a fork");
	else if (msg == 1)
		print_safe(ms, num, "is eating");
	else if (msg == 2)
		print_safe(ms, num, "is sleeping");
	else if (msg == 3)
		print_safe(ms, num, "is thinking");
	else if (msg == 4)
		print_safe(ms, num, "died");
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

int	ft_pow(int nb, int power)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	if (power < 0)
		return (0);
	while (i < power)
	{
		result *= nb;
		i++;
	}
	return (result);
}
