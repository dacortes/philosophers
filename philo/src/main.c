/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:21:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/15 11:16:01 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	tm_sleep(1 , &bx);
	pthread_mutex_unlock(&bx.sm_start);
	gettimeofday(&bx.start, NULL);
	status(&bx);
	tm_end(&bx);
	return (EXIT_SUCCESS);
}