/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:24:13 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/25 11:47:02 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int argc, char **argv)
{
    t_simulation *sim;
    int i;

    if (!check_args(argc, argv))
        error_exit("Invalid args");
    if (!(sim = malloc(sizeof(t_simulation))))
        error_exit("malloc failed");
    init_sim(sim, argv);
	if (!(sim->philo = malloc(sizeof(t_philo) * sim->philo_count)))
        error_exit("malloc failed for philos");
    if (!(sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philo_count)))
        error_exit("malloc failed for forks");
	init_fork_mutex(sim);
	pthread_mutex_init(&sim->print_lock, NULL);
	init_philo_and_thread(sim);
	pthread_create(&sim->monitor, NULL, monitor_func, (void *)sim);
	i = 0;
	while (i < sim->philo_count)
		pthread_join(sim->philo[i].thread, NULL);
	pthread_join(sim->monitor, NULL);
	i = 0;
	while (i < sim->philo_count)
		pthread_mutex_destroy(&sim->forks[i++]);
	free(sim->philo);
	free(sim->forks);
	free(sim);
}

