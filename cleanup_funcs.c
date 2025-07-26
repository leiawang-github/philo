/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:15 by leia              #+#    #+#             */
/*   Updated: 2025/07/26 16:14:18 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	error_exit(const char *msg)
{
	printf("❌ Error: %s\n", msg);
	exit(1);
}

void	destroy_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	destroy_forks_and_free(pthread_mutex_t *forks, int count)
{
	destroy_forks(forks, count);
	free(forks);
}

void	destroy_and_exit(t_simulation *sim, pthread_mutex_t *forks, int count,
		const char *msg)
{
	destroy_forks_and_free(forks, count);
	pthread_mutex_destroy(&sim->print_lock);
	error_exit(msg);
}

void	cleanup_simulation(t_simulation *sim, int fork_count)
{
	if (!sim)
		return ;
	if (sim->forks)
	{
		destroy_forks(sim->forks, fork_count);
		free(sim->forks);
	}
	if (sim->philo)
		free(sim->philo);
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->death_lock);
	free(sim);
}
