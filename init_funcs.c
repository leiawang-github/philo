/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:59:11 by leia              #+#    #+#             */
/*   Updated: 2025/07/26 16:23:27 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_struct(t_simulation *sim, char **argv)
{
	int	i;

	i = 0;
	if (!sim || !argv)
		error_exit("Invalid arguments to init_sim");
	sim->philo_count = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->start_time = 0;
	if (argv[5])
		sim->must_eat_count = ft_atoi(argv[5]);
	else
		sim->must_eat_count = -1;
	sim->someone_died = 0;
	sim->monitor = 0;
	sim->forks = NULL;
	sim->philo = NULL;
}

void	init_mutexes(t_simulation *sim)
{
	int	i;

	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
		error_exit("Failed to init print_lock");
	if (pthread_mutex_init(&sim->death_lock, NULL) != 0)
		error_exit("Failed to init death_lock");
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philo_count);
	if (!sim->forks)
	{
		pthread_mutex_destroy(&sim->print_lock);
		error_exit("malloc failed for forks");
	}
	i = 0;
	while (i < sim->philo_count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			destroy_and_exit(sim, sim->forks, i,
				"pthread_mutex_init failed for forks");
		i++;
	}
}

void	init_sim(t_simulation *sim, char **argv)
{
	if (!sim || !argv)
		error_exit("Invalid arguments to init_sim");
	init_struct(sim, argv);
	init_mutexes(sim);
}

void	init_philo(t_simulation *sim)
{
	int	i;

	i = 0;
	if (!sim)
		error_exit("Memory allocation failed");
	sim->philo = malloc(sizeof(t_philo) * sim->philo_count);
	if (!(sim->philo))
		error_exit("malloc failed for philos");
	while (i < sim->philo_count)
	{
		sim->philo[i].id = i + 1;
		sim->philo[i].left_fork = &sim->forks[i];
		sim->philo[i].right_fork = &sim->forks[(i + 1) % sim->philo_count];
		sim->philo[i].last_meal_time = sim->start_time;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].sim = sim;
		if (pthread_mutex_init(&sim->philo[i].meal_lock, NULL) != 0)
		{
			cleanup_simulation(sim, i);
			error_exit("pthread_mutex_init failed for meal_lock");
		}
		i++;
	}
}
