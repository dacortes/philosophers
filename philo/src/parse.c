/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:15:50 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 14:20:35 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *str)
{
	long int	num;
	int			sig;
	int			i;

	num = 0;
	sig = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		sig = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			break ;
		num = num * 10 + str[i] - 48;
		i++;
	}
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	return (num * sig);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

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
