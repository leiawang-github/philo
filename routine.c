/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:54:36 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/27 19:37:34 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	start_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->start_time = timestamp_ms();
	while (i < sim->count)
	{
		//sim->philo[i].last_meal_time = timestamp_ms();
		if (pthread_create(&sim->philo[i].thread, NULL, philo_routine,
				&sim->philo[i]) != 0)
			return (0);
		i++;
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!has_someone_died(philo->sim))
	{
		if (philo->sim->must_eat_count != -1
			&& philo->meals_eaten >= philo->sim->must_eat_count)
		{
			safe_print(philo->sim, "has finished eating", philo->id);
			break ;
		}
		philo_eat(philo);
		if (has_someone_died(philo->sim))
			break ;
		philo_sleep(philo);
		if (has_someone_died(philo->sim))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
