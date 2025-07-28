/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:54:36 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/28 12:57:24 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	start_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->start_time = timestamp_ms();
	sim->created_threads = 0;
	while (i < sim->count)
	{
		sim->philo[i].last_meal_time = timestamp_ms();
		if (pthread_create(&sim->philo[i].thread, NULL, philo_routine,
				&sim->philo[i]) != 0)
			return (0);
		sim->created_threads++;
		i++;
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_dead(philo->sim))
	{
		if (philo->sim->must_eat_count != -1
			&& philo->meals_eaten >= philo->sim->must_eat_count)
		{
			safe_print(philo->sim, "has finished eating", philo->id);
			break ;
		}
		philo_eat(philo);
		if (is_dead(philo->sim))
			break ;
		philo_sleep(philo);
		if (is_dead(philo->sim))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
