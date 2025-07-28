/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:24:13 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/28 07:41:08 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	int				i;

	if (!check_args(argc, argv))
		return (1);
	if (!init_all(&sim, argv))
	{
		cleanup_all(&sim);
		return (1);
	}
	start_threads(&sim);
	if (pthread_create(&sim.monitor, NULL, monitor_func, (void *)&sim) != 0)
	{
		destroy_and_exit(&sim);
		return (1);
	}
	pthread_join(&sim.monitor, NULL);
	i = 0;
	while (i < &sim.count)
		pthread_join(&sim.philo[i++].thread, NULL);
	cleanup_all(&sim);
	return (0);
}
