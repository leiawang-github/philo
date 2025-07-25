/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:54:36 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/25 14:39:34 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void philo_think(t_philo *philo)
{
	t_simulation *sim = philo->sim;

	safe_print(sim, "🤔 %ld Philo %d is thinking\n", timestamp_ms() - sim->start_time, philo->id);
}

static void philo_sleep(t_philo *philo)
{
	t_simulation *sim = philo->sim;

	safe_print(sim, "😴 %ld Philo %d is sleeping\n", timestamp_ms() - sim->start_time, philo->id);
	smart_sleep(sim->time_to_sleep, sim);
}

static void take_forks(t_philo *philo)
{
	t_simulation *sim = philo->sim;
	int id = philo->id;

	if (id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(sim, "🍴 %ld Philo %d takes left fork\n", timestamp_ms() - sim->start_time, id);
		pthread_mutex_lock(philo->right_fork);
		safe_print(sim, "🍴 %ld Philo %d takes right fork\n", timestamp_ms() - sim->start_time, id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print(sim, "🍴 %ld Philo %d takes right fork\n", timestamp_ms() - sim->start_time, id);
		pthread_mutex_lock(philo->left_fork);
		safe_print(sim, "🍴 %ld Philo %d takes left fork\n", timestamp_ms() - sim->start_time, id);
	}
}

static void drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void philo_eat(t_philo *philo)
{
	t_simulation *sim = philo->sim;

	take_forks(philo);
	safe_print(sim, "🥣 %ld Philo %d is eating\n", timestamp_ms() - sim->start_time, philo->id);
	philo->last_meal_time = timestamp_ms();
	smart_sleep(sim->time_to_eat, sim);
	philo->meals_eaten++;
	drop_forks(philo);
}


void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_simulation *sim = philo->sim;

	while ((sim->must_eat_count == -1 || philo->meals_eaten < sim->must_eat_count)
	       && !sim->someone_died)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return NULL;
}