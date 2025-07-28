/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:21:56 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/27 22:43:26 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_simulation *sim)
{
	long	now;
	long	last_meal;
	int		i;

	i = 0;
	pthread_mutex_lock(&sim->philo[i].meal_lock);
	last_meal = sim->philo[i].last_meal_time;
	pthread_mutex_unlock(&sim->philo[i].meal_lock);
	now = timestamp_ms();
	if (now - last_meal > sim->time_to_die)
	{
		pthread_mutex_lock(&sim->death_lock);
		sim->someone_died = 1;
		pthread_mutex_unlock(&sim->death_lock);
		pthread_mutex_lock(&sim->print_lock);
		printf("Philo %ld %d died\n", now - sim->start_time, sim->philo[i].id);
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
	while (1)
	{
		i = -1;
		while (++i < sim->count)
		{
			if (check_death(sim))
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	is_dead(t_simulation *sim)
{
	pthread_mutex_lock(&sim->death_lock);
	if (sim->someone_died)
		return (1);
	pthread_mutex_unlock(&sim->death_lock);
}
