/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:21:56 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/26 17:44:03 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_simulation *sim, t_philo *philo)
{
	long	now;
	long	last_meal;

	now = timestamp_ms();
	pthread_mutex_lock(&philo->meal_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (now - last_meal > sim->time_to_die)
	{
		pthread_mutex_lock(&sim->death_lock);
		if (!has_someone_died(philo->sim))
			sim->someone_died = 1;
		pthread_mutex_unlock(&sim->death_lock);
		pthread_mutex_lock(&sim->print_lock);
		printf("%ld %d died\n", now - sim->start_time, philo->id);
		pthread_mutex_unlock(&sim->print_lock);
		return (1);
	}
	return (0);
}

void	*monitor_func(void *arg)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)arg;
	while (!sim->someone_died)
	{
		i = 0;
		while (i < sim->philo_count)
		{
			if (check_death(sim, &sim->philo[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
