/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:21:56 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/28 13:59:36 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_simulation *sim, int i)
{
	long	now;
	long	last_meal;

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
		printf("%ld %d died\n", now - sim->start_time, sim->philo[i].id);
		pthread_mutex_unlock(&sim->print_lock);
		return (1);
	}
	return (0);
}

int	check_all_ate(t_simulation *sim)
{
	int	i;

	if (sim->must_eat_count == -1)
		return (0);
	i = 0;
	while (i < sim->count)
	{
		if (sim->philo[i].meals_eaten < sim->must_eat_count)
			return (0);
		i++;
	}
	return (1);
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
			if (check_death(sim, i))
				return (NULL);
		}
		if (check_all_ate(sim))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	is_dead(t_simulation *sim)
{
	int	status;

	pthread_mutex_lock(&sim->death_lock);
	status = sim->someone_died;
	pthread_mutex_unlock(&sim->death_lock);
	return (status);
}
