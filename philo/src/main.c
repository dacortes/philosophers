/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:21:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/13 15:52:09 by dacortes         ###   ########.fr       */
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



int	main(int ac, char **av)
{
	t_box box;

	get_arg (ac, av, check_av(ac, av), box.array);
	/* la sumulacion empieza cuando todo se crea */
	int i = 0;
	while (i < (ac - 1))
		printf("%d\n", box.array[i++]);
	return (EXIT_SUCCESS);
}