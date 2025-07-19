/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:56:16 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/11 12:56:32 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int is_digit(char c)
{
    if ('0' <= c && c <= '9')
        return (1);
    return (0);
}

int ft_atoi(char *str)
{
    int i;
    int res;
    int sign;

    i= 0;
    res = 0;
    sign = 1;
    while(str[i] == ' ' || str[i] == '\t' || (9 <= str[i] && str[i] <= 13))
        i++;
    if(str[i] == '-')
    {
        i++;
        sign = -sign;
    }
    else if (str[i] == '+')
        i++;
    while ('0' <= str[i] && str[i] <= '9')
    {
        res = res* 10 + str[i]
         - '0';
        i++;
    }
    return  res = res * sign;
}
