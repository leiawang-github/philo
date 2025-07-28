/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:40:33 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/27 19:21:23 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (is_digit(argv[i][j]) == 0)
				return (0);
			j++;
		}
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}
