/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:15 by leia              #+#    #+#             */
/*   Updated: 2025/07/25 10:58:18 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void cleanup_simulation(t_simulation *sim, int created_threads)
{
	if (sim->forks)
	{
		for (int i = 0; i < sim->philo_count; i++)
			pthread_mutex_destroy(&sim->forks[i]);
		free(sim->forks);
	}
	if (sim->philo)
		free(sim->philo);
	if (created_threads > 0)
	{
		for (int i = 0; i < created_threads; i++)
			pthread_join(sim->philo[i].thread, NULL);
	}
}
