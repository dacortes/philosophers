/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:21:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/14 14:54:47 by dacortes         ###   ########.fr       */
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

int	init(t_box *bx, int ac)
{
	bx->n_philo = bx->arr[0];
	bx->tm_die = bx->arr[1];
	bx->tm_eat = bx->arr[2];
	bx->tm_sleep = bx->arr[3];
	bx->tm_mt_eat = NOT;
	(ac == 5) && (bx->tm_mt_eat = bx->arr[4]);
	bx->philo = malloc(bx->n_philo * sizeof(t_philo));
	bx->th = malloc(bx->n_philo * sizeof(pthread_t));
	if (!bx->philo || !bx->th)
		exit ((printf(R"Error➜"E" memory allocation") * 0) + ERROR);
	pthread_mutex_init(&bx->mt_print, NULL);
	pthread_mutex_init(&bx->sm_start, NULL);
	return  (EXIT_SUCCESS);
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