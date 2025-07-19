/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:54:36 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/14 18:34:15 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *philo_routine(void *arg)
{
	t_philo *philos = (t_philo *)arg;

	while (
		(philos->must_eat_count == -1 || philos->meals_eaten < philos->must_eat_count) &&
		!philos->someone_died
	)
	if (philos->someone_died)
        break;
	{
		int id = philos->id;
		int left = id % philos->fork_count;
		int right = (id + 1) % philos->fork_count;

		if (id % 2 == 0)
		{
			pthread_mutex_lock(&philos->forks[left]);
			printf("🍴 %ld Philo %d takes left fork\n", timestamp_ms() - philos->start_time, id);
			pthread_mutex_lock(&philos->forks[right]);
			printf("🍴 %ld Philo %d takes right fork\n", timestamp_ms() - philos->start_time, id);
		}
		else
		{
			pthread_mutex_lock(&philos->forks[right]);
			printf("🍴 %ld Philo %d takes right fork\n", timestamp_ms() - philos->start_time, id);
			pthread_mutex_lock(&philos->forks[left]);
			printf("🍴 %ld Philo %d takes left fork\n", timestamp_ms() - philos->start_time, id);
		}
		printf("🥣 %ld Philo %d is eating\n", timestamp_ms() - philos->start_time, id);
		philos->last_meal_time = timestamp_ms();
		smart_sleep(philos->time_to_eat, philos);
		philos->meals_eaten++;

		pthread_mutex_unlock(&philos->forks[left]);
		pthread_mutex_unlock(&philos->forks[right]);

		printf("😴 %ld Philo %d is sleeping\n", timestamp_ms() - philos->start_time, id);
		smart_sleep(philos->time_to_eat, philos);

		printf("🤔 %ld Philo %d is thinking\n", timestamp_ms() - philos->start_time, id);
	}
	return NULL;
}
