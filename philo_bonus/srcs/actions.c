/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:04:23 by agruet            #+#    #+#             */
/*   Updated: 2025/03/19 15:06:59 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	can_eat(t_philo *philo, t_data *data)
{
	if (philo->fork1 == false)
	{
		if (sem_wait(data->fork_sem))
			return (0);
		philo->fork1 = true;
		print_msg(philo->num, data, 0);
	}
	if (philo->fork2 == false)
	{
		if (sem_wait(data->fork_sem))
			return (sem_post(data->fork_sem), 0);
		philo->fork2 = true;
		print_msg(philo->num, data, 0);
	}
	return (1);
}

void	philo_eat(t_philo *philo, t_data *data)
{
	if (get_time_now() > philo->last_eat + data->time_to_die)
		die(philo, data);
	philo->last_eat = get_time_now();
	print_msg(philo->num, data, 1);
	if (data->time_to_die < data->time_to_eat)
		usleep(data->time_to_die * 1000);
	else
		usleep(data->time_to_eat * 1000);
	release_forks(philo, data);
	is_finished(philo, data);
	philo_sleep(philo, data);
}

void	philo_sleep(t_philo *philo, t_data *data)
{
	long	ts;

	if (get_time_now() > philo->last_eat + data->time_to_die)
		die(philo, data);
	print_msg(philo->num, data, 2);
	ts = get_time_now();
	if (philo->last_eat + data->time_to_die < ts + data->time_to_sleep)
	{
		usleep((philo->last_eat + data->time_to_die - ts) * 1000);
		die(philo, data);
	}
	else
	{
		usleep(data->time_to_sleep * 1000);
		philo_think(philo, data, false);
	}
}

void	philo_think(t_philo *philo, t_data *data, bool first_think)
{
	print_msg(philo->num, data, 3);
	if (first_think == true)
		usleep(data->time_to_eat * 1000);
	else
		usleep(1000);
	while (!can_eat(philo, data))
	{
		if (get_time_now() > philo->last_eat + data->time_to_die)
			die(philo, data);
		usleep(10);
	}
	philo_eat(philo, data);
}

void	die(t_philo *philo, t_data *data)
{
	if (philo->fork1 == true)
		sem_post(data->fork_sem);
	if (philo->fork2 == true)
		sem_post(data->fork_sem);
	sem_close(data->fork_sem);
	sem_close(data->finish_sem);
	sem_close(data->quit_sem);
	print_msg(philo->num, data, 4);
	exit(EXIT_FAILURE);
}
