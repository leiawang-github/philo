/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:40:33 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/14 15:12:56 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int check_args(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    if (argc != 5 && argc != 6)
        error_exit("Invalid number of arguments.");
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (is_digit(argv[i][j]) == 0)
                error_exit("All arguments must be digits.");
            j++;
        }
        i++;
    }
    return (1);
}



void error_exit(char *msg)
{
    printf("❌ Error: %s\n", msg);
    exit(1);
}
