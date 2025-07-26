/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:13:09 by leia              #+#    #+#             */
/*   Updated: 2025/07/26 16:01:47 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philo *philo)
{
	if (has_someone_died(philo->sim))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		if (has_someone_died(philo->sim))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return ;
		}
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		if (has_someone_died(philo->sim))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
	}
	safe_print(philo->sim, "get two forks!", philo->id);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo)
{
	if (has_someone_died(philo->sim))
		return ;
	take_forks(philo);
	if (has_someone_died(philo->sim))
	{
		drop_forks(philo);
		return ;
	}
	safe_print(philo->sim, "is eating", philo->id);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = timestamp_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	smart_sleep(philo->sim->time_to_eat, philo->sim);
	philo->meals_eaten++;
	drop_forks(philo);
}

void	philo_think(t_philo *philo)
{
	if (has_someone_died(philo->sim))
		return ;
	safe_print(philo->sim, "is thinking", philo->id);
}

void	philo_sleep(t_philo *philo)
{
	if (has_someone_died(philo->sim))
		return ;
	safe_print(philo->sim, "is sleeping", philo->id);
	smart_sleep(philo->sim->time_to_sleep, philo->sim);
}
