/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:21:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/22 10:42:16 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
/* memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock */
/* parameters 
num philo and fork, time to die(ms), time to eat, time to sleep(ms)
int _fork[num_fork];
*/

int	check_av(int ac, char **av)
{
	int	check;

	if (ac < 5 || ac > 6)
		exit ((printf(R"Error➜"E"Invalid arguments\n") * 0) + ERROR);
	check = is_digit(av[1]) * is_digit(av[2]) * is_digit(av[3]) * is_digit(av[4]);
	if (ac == 6)
		check = is_digit(av[1]) * is_digit(av[2]) * is_digit(av[3])
			* is_digit(av[4]) * is_digit(av[5]);
	if (!check)
		exit ((printf(R"Error➜"E"Invalid arguments\n") * 0) + ERROR);
	return (printf(C"Welcome to the black box 🗃\n"E) * TRUE);
}

int	init(int ac, char **av, int	check)
{
	int	array[ac - 1];
	int	i;
	int j;

	if (check)
	{
		i = 0;
		j = 1;
		while (i < ac)
		{
			array[i] = ft_atoi(av[j]);
			printf("array[%i]=%d\n", i, array[i]);
			if (array[i] <= 0)
			{
				exit((printf(R"Error➜Do you want the box to explode?"E"\n")
					* 0) + ERROR);
			}
			i++;
			j++;
		}
		return (TRUE);
	}
	else
		exit((printf(R"Error➜The box exploded"E"\n") * 0) + ERROR);
}

int	main(int ac, char **av)
{
	(void)av;
	init (ac, av, check_av(ac, av));
	printf("die %d\n", ft_atoi("0000000000000000a"));
	return (EXIT_SUCCESS);
}
