/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:20:51 by agruet            #+#    #+#             */
/*   Updated: 2025/05/05 11:49:48 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	is_finished(t_philo *philo, t_data *data)
{
	philo->eating_count++;
	if (data->times_must_eat != -1 && philo->finished_eating == false
		&& philo->eating_count >= data->times_must_eat)
		sem_post(data->finish_sem);
}

void	release_forks(t_philo *philo, t_data *data)
{
	philo->fork1 = false;
	philo->fork2 = false;
	sem_post(data->fork_sem);
	sem_post(data->fork_sem);
}
