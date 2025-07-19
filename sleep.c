/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:14:12 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/14 18:35:12 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void smart_sleep(int ms, t_philo *rules)
{
    long start = timestamp_ms();
    while (timestamp_ms() - start < ms)
    {
        if (rules->someone_died)
            break;
        usleep(100); // 微小睡眠以减轻 CPU 占用
    }
}

