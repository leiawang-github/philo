/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:15 by leia              #+#    #+#             */
/*   Updated: 2025/07/28 13:40:37 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	print_error(int err_code)
{
	if (err_code == ERR_ARGC)
		printf("Error: Invalid number of arguments.\n");
	else if (err_code == ERR_ARGV)
		printf("Error: Argument contains only positive digits.\n");
	else if (err_code == ERR_MALLOC)
		printf("Error: Memory allocation failed.\n");
	else if (err_code == ERR_THREAD)
		printf("Error: Failed to create thread.\n");
	else if (err_code == ERR_MUTEX)
		printf("Error: Mutex initialization failed.\n");
	else
		printf("Error: Unknown error occurred.\n");
	return (0);
}

void	destroy_philo(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->count)
	{
		pthread_mutex_destroy(&sim->philo[i].meal_lock);
		i++;
	}
	free(sim->philo);
}

void	destroy_forks(t_simulation *sim)
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

void	destroy_mutexex(t_simulation *sim)
{
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->death_lock);
}

void	clean_all(t_simulation *sim)
{
	destroy_philo(sim);
	destroy_forks(sim);
	destroy_mutexex(sim);
}
