/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:54:36 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/22 19:57:07 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_simulation *sim = philo->sim;

	while ((sim->must_eat_count == -1 || philo->meals_eaten < sim->must_eat_count) &&
	       !sim->someone_died)
	{
		int id = philo->id;
		int left = id % philo->fork_count;
		int right = (id + 1) % philo->fork_count;

		if (id % 2 == 0)
		{
			pthread_mutex_lock(&philo->forks[left]);
			printf("🍴 %ld Philo %d takes left fork\n", timestamp_ms() - sim->start_time, id);
			pthread_mutex_lock(&philo->forks[right]);
			printf("🍴 %ld Philo %d takes right fork\n", timestamp_ms() - sim->start_time, id);
		}
		else
		{
			pthread_mutex_lock(&philo->forks[right]);
			printf("🍴 %ld Philo %d takes right fork\n", timestamp_ms() - sim->start_time, id);
			pthread_mutex_lock(&philo->forks[left]);
			printf("🍴 %ld Philo %d takes left fork\n", timestamp_ms() - sim->start_time, id);
		}

		printf("🥣 %ld Philo %d is eating\n", timestamp_ms() - sim->start_time, id);
		philo->last_meal_time = timestamp_ms();
		smart_sleep(sim->time_to_eat, sim);
		philo->meals_eaten++;

		pthread_mutex_unlock(&philo->forks[left]);
		pthread_mutex_unlock(&philo->forks[right]);

		printf("😴 %ld Philo %d is sleeping\n", timestamp_ms() - sim->start_time, id);
		smart_sleep(sim->time_to_sleep, sim);

		printf("🤔 %ld Philo %d is thinking\n", timestamp_ms() - sim->start_time, id);
	}

	return NULL;
}
