/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:24:13 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/28 13:40:57 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	handle_one_philo(char **argv)
{
	long	now;

	if (ft_atoi(argv[1]) == 1)
	{
		now = timestamp_ms();
		printf("%d 1 has taken a fork\n", 0);
		usleep(ft_atoi(argv[2]) * 1000);
		now = timestamp_ms();
		printf("%d 1 died\n", ft_atoi(argv[2]));
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;
	int				i;

	if (!check_args(argc, argv))
		return (1);
	if (ft_atoi(argv[1]) == 1)
		return (handle_one_philo(argv));
	if (!init_all(&sim, argv))
	{
		clean_all(&sim);
		return (1);
	}
	start_threads(&sim);
	if (pthread_create(&sim.monitor, NULL, monitor_func, (void *)&sim) != 0)
	{
		clean_all(&sim);
		return (1);
	}
	pthread_join(sim.monitor, NULL);
	i = 0;
	i = 0;
	while (i < sim.created_threads)
		pthread_join(sim.philo[i++].thread, NULL);
	clean_all(&sim);
	return (0);
}
