/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:04:23 by agruet            #+#    #+#             */
/*   Updated: 2025/04/18 19:12:02 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	grab_forks(t_philo *philo, t_data *data)
{
	if (philo->fork1 == false)
	{
		if (!data->fork_sem | sem_wait(data->fork_sem))
			return (0);
		philo->fork1 = true;
		print_msg(philo->num, data, 0);
	}
	if (philo->fork2 == false)
	{
		if (!data->fork_sem || sem_wait(data->fork_sem))
			return (sem_post(data->fork_sem), 0);
		philo->fork2 = true;
		print_msg(philo->num, data, 0);
	}
	return (1);
}

int	philo_eat(t_philo *philo, t_data *data, t_monitor *death_monitor)
{
	sem_wait(death_monitor->death_sem);
	death_monitor->last_eat = get_time_now();
	sem_post(death_monitor->death_sem);
	print_msg(philo->num, data, 1);
	ft_usleep(data->time_to_eat * 1000);
	release_forks(philo, data);
	is_finished(philo, data);
	return (0);
}

int	philo_sleep(t_philo *philo, t_data *data)
{
	print_msg(philo->num, data, 2);
	ft_usleep(data->time_to_sleep * 1000);
	return (0);
}

int	philo_think(t_philo *philo, t_data *data, bool first_think)
{
	print_msg(philo->num, data, 3);
	if (first_think == true)
		ft_usleep(data->time_to_eat * 1000);
	else
		ft_usleep(1000);
	while (!grab_forks(philo, data))
		ft_usleep(10);
	return (0);
}

void	die(t_philo *philo, t_data *data, t_monitor *monitor)
{
	print_msg(philo->num, data, 4);
	close_all(data, monitor);
	exit(EXIT_FAILURE);
}
