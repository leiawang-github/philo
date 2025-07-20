/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:54:36 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/20 11:31:22 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *philo_routine(void *arg)
{
	t_simulation *sim = (t_simulation *)arg;

	while (
		(sim->must_eat_count == -1 || sim->philos->meals_eaten < sim->must_eat_count) &&
		!sim->someone_died
	)
	if (sim->someone_died)
        break;
	{
		int id = sim->philos->id;
		int left = id % sim->philos->fork_count;
		int right = (id + 1) % sim->philos->fork_count;

		if (id % 2 == 0)
		{
			pthread_mutex_lock(&sim->philos->forks[left]);
			printf("🍴 %ld Philo %d takes left fork\n", timestamp_ms() - sim->start_time, id);
			pthread_mutex_lock(&sim->philos->forks[right]);
			printf("🍴 %ld Philo %d takes right fork\n", timestamp_ms() - sim->start_time, id);
		}
		else
		{
			pthread_mutex_lock(&sim->philos->forks[right]);
			printf("🍴 %ld Philo %d takes right fork\n", timestamp_ms() - sim->start_time, id);
			pthread_mutex_lock(&sim->philos->forks[left]);
			printf("🍴 %ld Philo %d takes left fork\n", timestamp_ms() - sim->start_time, id);
		}
		printf("🥣 %ld Philo %d is eating\n", timestamp_ms() - sim->start_time, id);
		sim->philos->last_meal_time = timestamp_ms();
		smart_sleep(sim->time_to_eat, sim);
		sim->philos->meals_eaten++;

		pthread_mutex_unlock(&sim->philos->forks[left]);
		pthread_mutex_unlock(&sim->philos->forks[right]);

		printf("😴 %ld Philo %d is sleeping\n", timestamp_ms() - sim->start_time, id);
		smart_sleep(sim->time_to_eat,sim);

		printf("🤔 %ld Philo %d is thinking\n", timestamp_ms() - sim->start_time, id);
	}
	return NULL;
}
