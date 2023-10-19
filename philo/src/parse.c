/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:16:25 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/19 11:00:22 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_av(int ac, char **av)
{
	int	check;

	if (ac < 5 || ac > 6)
		exit ((printf(R"Error➜"E" Invalid arguments\n") * 0) + ERROR);
	check = is_digit(av[1]) * is_digit(av[2]) * is_digit(av[3])
		* is_digit(av[4]);
	if (ac == 6)
		check = is_digit(av[1]) * is_digit(av[2]) * is_digit(av[3])
			* is_digit(av[4]) * is_digit(av[5]);
	if (!check)
		exit ((printf(R"Error➜"E" Invalid arguments\n") * 0) + ERROR);
	return (printf(C"Welcome to the black box 🗃\n"E) * TRUE);
}

int	get_arg(int ac, char **av, int check, int *array)
{
	int	i;
	int	j;

	if (check)
	{
		i = 0;
		j = 1;
		while (i < (ac - 1))
		{
			array[i] = ft_atoi(av[j]);
			if (array[0] >= 201)
				exit (printf(R"Error➜"E" The maximum number of"\
				" philosophers is 200\n"));
			if (array[i] <= 0)
				exit ((printf(R"Error➜"E" Do you want the box to explode?\n")
						* 0) + ERROR);
			i++;
			j++;
		}
		return (TRUE);
	}
	else
		exit((printf(R"Error➜"E" The box exploded\n") * 0) + ERROR);
}
