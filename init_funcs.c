/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:59:11 by leia              #+#    #+#             */
/*   Updated: 2025/07/28 12:57:36 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_mutex(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&sim->death_lock, NULL) != 0)
		return (0);
	return (1);
}

int	init_philo(t_simulation *sim)
{
	int	i;

	sim->philo = malloc(sizeof(t_philo) * sim->count);
	if (!sim->philo)
		return (0);
	i = 0;
	while (i < sim->count)
	{
		sim->philo[i].id = i + 1;
		sim->philo[i].left_fork = &sim->forks[i];
		sim->philo[i].right_fork = &sim->forks[(i + 1) % sim->count];
		sim->philo[i].last_meal_time = 0;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].sim = sim;
		if (pthread_mutex_init(&sim->philo[i].meal_lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->philo[i].meal_lock);
			free(sim->philo);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_sim(t_simulation *sim, char **argv)
{
	int	i;

	i = -1;
	sim->count = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->start_time = 0;
	if (argv[5])
		sim->must_eat_count = ft_atoi(argv[5]);
	else
		sim->must_eat_count = -1;
	sim->someone_died = 0;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->count);
	if (!sim->forks)
		return (0);
	while (++i < sim->count)
		pthread_mutex_init(&sim->forks[i], NULL);
	return (1);
}

int	init_all(t_simulation *sim, char **argv)
{
	if (!init_sim(sim, argv))
	{
		destroy_forks(sim);
		return (0);
	}
	if (!init_mutex(sim))
	{
		destroy_mutexex(sim);
		return (0);
	}
	if (!init_philo(sim))
	{
		clean_all(sim);
		return (0);
	}
	return (1);
}
