/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:40:33 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/28 13:27:17 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
		return (print_error(ERR_ARGC));
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (is_digit(argv[i][j]) == 0)
				return (print_error(ERR_ARGV));
			j++;
		}
		if (ft_atoi(argv[i]) < 0)
			return (print_error(ERR_ARGV));
		i++;
	}
	return (1);
}
