/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:24:13 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/26 16:10:22 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_simulation	*sim;
	int				i;

	if (!check_args(argc, argv))
		return (1);
	sim = malloc(sizeof(t_simulation));
	if (!(sim))
		error_exit("malloc failed for simulation");
	init_sim(sim, argv);
	init_philo(sim);
	start_threads(sim);
	if (pthread_create(&sim->monitor, NULL, monitor_func, (void *)sim) != 0)
		destroy_and_exit(sim, sim->forks, sim->philo_count,
			"pthread_create failed for monitor");
	pthread_join(sim->monitor, NULL);
	i = 0;
	while (i < sim->philo_count)
		pthread_join(sim->philo[i++].thread, NULL);
	cleanup_simulation(sim, sim->philo_count);
	return (0);
}
