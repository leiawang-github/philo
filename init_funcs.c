/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:59:11 by leia              #+#    #+#             */
/*   Updated: 2025/07/25 11:58:50 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void init_sim(t_simulation *sim, char **argv)
{
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

void init_philo_and_thread(t_simulation *sim)
{
	int i;
	i = 0; 
	if (!sim->philo || !sim)
        error_exit("Memory allocation failed");

	while (i < sim->philo_count)
	{
		sim->philo[i].id = i + 1;
		sim->philo[i].left_fork = &sim->forks[i];
		sim->philo[i].right_fork= &sim->forks[(i + 1) % sim->philo_count]; 
		sim->philo[i].last_meal_time = timestamp_ms();
		sim->philo[i].meals_eaten = 0;	
		sim->philo[i].sim = sim;
		if(pthread_create(&sim->philo[i].thread, NULL, philo_routine, (void *)&sim->philo[i]) !=0)
		{
			cleanup_simulation(sim, i);
			error_exit("Thread creation failed"); 
		}
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


