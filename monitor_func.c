/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:21:56 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/25 11:50:10 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *monitor_func(void *arg)
{
	t_simulation *sim = (t_simulation *)arg;
	int i;
	long now;
	long last_eat;

	while (1)
	{
		i = 0;
		while (i < sim->philo_count)
		{
			now = timestamp_ms();
			last_eat = sim->philo[i].last_meal_time;
			if (now - last_eat >= sim->time_to_die)
			{
				printf("%ld %d died\n",
					now - sim->start_time, sim->philo[i].id);
				sim->someone_died = 1;
				break;
			}
			i++;
		}
		if (sim->someone_died)
            break;
		usleep(1000);
	}
	return NULL;
}

