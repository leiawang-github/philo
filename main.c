/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:24:13 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/20 21:39:27 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void init_rules(t_simulation *sim, char **argv)
{
	printf("At least we get here!");
	sim->philo_count = ft_atoi(argv[1]);
    sim->time_to_die = ft_atoi(argv[2]);
    sim->time_to_eat = ft_atoi(argv[3]);
    sim->time_to_sleep = ft_atoi(argv[4]);
	sim->start_time = timestamp_ms();

    if(argv[5])
		sim->must_eat_count = ft_atoi(argv[5]);
    else
		sim->must_eat_count = -1;
    sim->someone_died = 0;
}

void init_philos_and_threads(t_simulation *sim)
{
	int i;
	i = 0;
	if (!sim->philos || !sim->threads || !sim->forks)
    {
        error_exit("Memory allocation failed");
    }
	while (i < sim->philo_count)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].forks = sim->forks;
		sim->philos[i].fork_count = sim->philo_count;
		sim->philos[i].last_meal_time = timestamp_ms();
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].sim = sim;
		pthread_create(&sim->threads[i], NULL, philo_routine, (void *)&sim->philos[i]);
		i++;
	}
}

void init_fork_mutex(t_simulation *sim)
{
	int i;

	i = 0;
	while (i < sim->philo_count)
		pthread_mutex_init(&sim->forks[i++], NULL);
}

