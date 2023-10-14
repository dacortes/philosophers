/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:21:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/14 18:11:08 by dacortes         ###   ########.fr       */
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

void	show_ln(t_philo *ph, char *str)
{
	int	i;
	int	end;
	i = tm_elapsed(ph->bx->start);
	pthread_mutex_lock(&ph->bx->mt_print);
	pthread_mutex_lock(&ph->bx->sm_end);
	end = ph->bx->end_of_sm;
	pthread_mutex_unlock(&ph->bx->sm_end);
	if (end != 1)
		printf("%d %d %s\n", i, (ph->num + 1), str);
	pthread_mutex_unlock(&ph->bx->mt_print);
}

int	main(int ac, char **av)
{
	t_box bx;

	get_arg (ac, av, check_av(ac, av), bx.arr);
	init(&bx, (ac - 1));
	printf(R"%d\n"E, (ac - 1));
	printf("num philos %d\n", bx.n_philo);
	printf("tm_to_die %d\n", bx.tm_die);
	printf("tm_to_eat %d\n", bx.tm_eat);
	printf("tm_to_sleep %d\n", bx.tm_sleep);
	(((ac - 1) == 5) && printf("number_of_times_each_philosopher_must_eat %d\n", bx.tm_mt_eat));
	int i = 0;
	while (i < (ac - 1))
		printf(C"arr[%d]\n"E, bx.arr[i++]);
	return (EXIT_SUCCESS);
}