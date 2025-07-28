/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:14:12 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/28 09:09:36 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	smart_sleep(long duration, t_simulation *sim)
{
	long	start;

	start = timestamp_ms();
	while ((timestamp_ms() - start) < duration)
	{
		if (is_dead(sim))
			break ;
		usleep(100);
	}
}
