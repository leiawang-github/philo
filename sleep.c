/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:14:12 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/20 11:31:48 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void smart_sleep(int ms, t_simulation *sim)
{
    long start = timestamp_ms();
    while (timestamp_ms() - start < ms)
    {
        if (sim->someone_died)
            break;
        usleep(100); // 微小睡眠以减轻 CPU 占用
    }
}

