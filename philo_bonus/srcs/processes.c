/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:12:28 by agruet            #+#    #+#             */
/*   Updated: 2025/04/18 18:53:58 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_action	first_action(t_data *data, t_philo *philo, t_monitor *monitor)
{
	if (philo->num == 0 && data->number_of_philosophers % 2 == 1)
	{
		philo_think(philo, data, false);
		philo_eat(philo, data, monitor);
		return (EATING);
	}
	if (philo->num % 2 == 0)
	{
		if (grab_forks(philo, data) == 0)
			return (DYING);
		philo_eat(philo, data, monitor);
		return (EATING);
	}
	else
	{
		philo_think(philo, data, true);
		return (THINKING);
	}
}

void	philo_start(t_data *data, t_philo *philo, t_routine *routine_param)
{
	t_action	action;

	start_monitoring(routine_param);
	action = first_action(data, philo, routine_param->monitor);
	if (action == DYING)
		return ;
	while (true)
	{
		action++;
		if (action > THINKING)
			action = EATING;
		if (action == EATING && philo_eat(philo, data, routine_param->monitor))
			return ;
		else if (action == SLEEPING && philo_sleep(philo, data))
			return ;
		else if (action == THINKING && philo_think(philo, data, false))
			return ;
	}
}

int	initialize_sems(t_data *data, t_philo *philo, t_monitor *monitor)
{
	long	size;
	long	i;

	size = 1;
	sem_wait(data->finish_sem);
	sem_wait(data->quit_sem);
	memset(monitor->sem_name, 0, 5);
	monitor->sem_name[0] = 'p';
	while (philo->num + 1 > ft_pow(10, size))
		size++;
	monitor->sem_name[size + 1] = 0;
	i = 1;
	while (size > 0)
		monitor->sem_name[i++] = philo->num / ft_pow(10, --size) % 10 + '0';
	sem_unlink(monitor->sem_name);
	monitor->death_sem = sem_open(monitor->sem_name, O_CREAT, 0644, 1);
	ft_usleep(10000);
	if (monitor->death_sem == SEM_FAILED)
		return (0);
	return (1);
}

void	*new_process(t_data *data, int nb)
{
	t_philo		philo;
	t_routine	routine_param;
	t_monitor	monitor;

	free(data->pids);
	philo.num = nb;
	if (!initialize_sems(data, &philo, &monitor))
		(close_all(data, &monitor), exit(EXIT_FAILURE));
	philo.eating_count = 0;
	philo.finished_eating = false;
	monitor.last_eat = get_time_now();
	philo.fork1 = false;
	philo.fork2 = false;
	if (data->times_must_eat == 0)
		(close_all(data, &monitor), exit(EXIT_FAILURE));
	routine_param.data = data;
	routine_param.philo = &philo;
	routine_param.monitor = &monitor;
	philo_start(data, &philo, &routine_param);
	while (1)
		ft_usleep(100000);
	return (NULL);
}
