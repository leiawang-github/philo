/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:24:13 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/19 18:01:01 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void init_rules(t_simulation *sim, char **argv)
{
	printf("At least we get here!");
	sim->philos->philo_count = ft_atoi(argv[1]);
    sim->philos->time_to_die = ft_atoi(argv[2]);
    sim->philos->time_to_eat = ft_atoi(argv[3]);
    sim->philos->time_to_sleep = ft_atoi(argv[4]);

    if(argv[5])
		sim->philos->must_eat_count = ft_atoi(argv[5]);
    else
		sim->philos->must_eat_count = -1;
    sim->philos->someone_died = 0;
}

void init_philos_and_threads(t_simulation *sim)
{
	int i;
	i = 0;

	while (i < sim->philos->philo_count)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].forks = sim->forks;
		sim->philos[i].fork_count = sim->philos->philo_count;
		sim->philos[i].last_meal_time = timestamp_ms();
		sim->philos[i].meals_eaten = 0;
		pthread_create(&sim->threads[i], NULL, philo_routine, (void *)&sim->philos[i]);
		i++;
	}
}

void init_fork_mutex(t_simulation *sim)
{
	int i;

	i = 0;
	while (i < sim->philos->philo_count)
		pthread_mutex_init(&sim->forks[i++], NULL);
}

int	main(int argc, char **argv)
{
	printf("hey there");
	t_simulation	*sim;
	int				i;

	if (!check_args(argc, argv))
		error_exit("Invalid args");
	sim = malloc(sizeof(t_simulation));
	if (!sim)
		error_exit("malloc failed");

	init_rules(sim, argv);
	printf("init OK!!");

	sim->philos = malloc(sizeof(t_philo) * sim->philos->philo_count);
	sim->threads = malloc(sizeof(pthread_t) * sim->philos->philo_count);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philos->philo_count);

	init_philos_and_threads(sim);

	init_fork_mutex(sim);
	pthread_create(&sim->monitor, NULL, monitor_func, (void *)sim->philos);
	i = 0;
	while (i < sim->philos->philo_count)
		pthread_join(sim->threads[i++], NULL);
	pthread_join(sim->monitor, NULL);
	i = 0;
	while (i < sim->philos->philo_count)
		pthread_mutex_destroy(&sim->forks[i++]);
	free(sim->philos);
	free(sim->threads);
	free(sim->forks);
	free(sim);
}
