/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:51 by agruet            #+#    #+#             */
/*   Updated: 2025/03/18 17:20:32 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	if (data->quit_sem)
		return ;
	sem_close(data->quit_sem);
	sem_unlink("/quit");
}

void	print_msg(long num, t_data *data, int msg)
{
	long	ms;

	ms = get_sim_time(data);
	if (msg == 0)
		new_printf(ms, num, "has taken a fork");
	else if (msg == 1)
		new_printf(ms, num, "is eating");
	else if (msg == 2)
		new_printf(ms, num, "is sleeping");
	else if (msg == 3)
		new_printf(ms, num, "is thinking");
	else if (msg == 4)
		new_printf(ms, num, "died");
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
