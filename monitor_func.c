/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:21:56 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/14 18:36:47 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *monitor_func(void *arg)
{
	t_philo *philos = (t_philo* )arg;
	int i;
	long now;
	long last_eat;


	while (1)
	{
		i = 0;
		while (i < philos[0].philo_count)
		{

			now = timestamp_ms();
			last_eat = philos[i].last_meal_time;
			if (now - last_eat >= philos[i].time_to_die)
			{
				printf("%ld %d died\n", timestamp_ms() - philos[i].start_time, philos[i].id);
				philos->someone_died = 1;
				return NULL;
			}
			i++;
		}
		usleep(1000);
	}
	return NULL;
}
