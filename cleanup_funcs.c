/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:15 by leia              #+#    #+#             */
/*   Updated: 2025/07/28 07:39:03 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	error_exit(const char *msg) ///
{
	if (msg == NULL)
	{
		printf("❌ Error: Unknown error occurred\n");
		exit(1);
	}
	if (strcmp(msg, "malloc failed for philos") == 0)
	{
		printf("❌ Error: %s\n", msg);
		exit(1);
	}
}

void	destroy_mutexex(t_simulation *sim)
{
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->death_lock);
	pthread_mutex_destroy(&sim->philo->meal_lock);
}

void	destroy_and_free_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->forks);
}

void	destroy_and_free_philo(t_simulation *sim)
{
	pthread_destroy_mutex(&sim->philo->right_fork);
	pthread_destroy_mutex(&sim->philo->left_fork);
	free(sim->philo);
}

void	clean_all(t_simulation *sim)
{
	destroy_mutexex(sim);
	destroy_and_free_forks(sim);
	destroy_and_free_philo(sim);
}