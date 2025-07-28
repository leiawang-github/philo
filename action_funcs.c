/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:13:09 by leia              #+#    #+#             */
/*   Updated: 2025/07/28 12:35:02 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philo *philo)
{
	int	i;

	i = 0;
	if (is_dead(philo->sim))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = timestamp_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	safe_print(philo->sim, "get two forks!", philo->id);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo)
{
	if (is_dead(philo->sim))
		return ;
	take_forks(philo);
	safe_print(philo->sim, "is eating", philo->id);
	smart_sleep(philo->sim->time_to_eat, philo->sim);
	philo->meals_eaten++;
}

void	philo_think(t_philo *philo)
{
	if (is_dead(philo->sim))
		return ;
	safe_print(philo->sim, "is thinking", philo->id);
}

void	philo_sleep(t_philo *philo)
{
	if (is_dead(philo->sim))
		return ;
	safe_print(philo->sim, "is sleeping", philo->id);
	smart_sleep(philo->sim->time_to_sleep, philo->sim);
}
