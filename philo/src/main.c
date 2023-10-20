/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:21:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 12:25:37 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	end_sm(t_box *box)
{
	int	id;

	id = 0;
	while (id < box->n_philo)
	{
		pthread_mutex_destroy(&box->ph[id].left);
		pthread_mutex_destroy(&box->ph[id].m_die);
		id++;
	}
	pthread_mutex_destroy(&box->m_start);
	pthread_mutex_destroy(&box->m_sttus);
	pthread_mutex_destroy(&box->m_endph);
	pthread_mutex_destroy(&box->m_endsm);
	if (box->ph)
		free(box->ph);
	if (box->th)
		free(box->th);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_box	box;
	int		arr[5];

	get_arg (ac, av, check_av(ac, av), arr);
	init(&box, arr, (ac - 1));
	tm_sleep(&box, 100);
	gettimeofday(&box.start, NULL);
	pthread_mutex_unlock(&box.m_start);
	supervisor(&box);
	end_sm(&box);
	return (EXIT_SUCCESS);
}
