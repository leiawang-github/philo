/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:54:28 by leia              #+#    #+#             */
/*   Updated: 2025/07/26 15:58:01 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	has_someone_died(t_simulation *sim)
{
	int	died;

	pthread_mutex_lock(&sim->death_lock);
	died = sim->someone_died;
	pthread_mutex_unlock(&sim->death_lock);
	return (died);
}
