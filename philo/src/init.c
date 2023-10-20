/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:08:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 11:51:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_th(t_box *box)
{
	int	id;

	id = 0;
	while (id < box->n_philo)
	{
		if (pthread_create(&box->th[id], NULL, run, &box->ph[id]) != 0)
			exit ((printf(R"Error➜"E" Create threads\n") * 0) + ERROR);
		id++;
	}
	return (EXIT_FAILURE);
}

static int	init_ph(t_box *box)
{
	int	id;

	id = 0;
	pthread_mutex_lock (&box->m_start);
	while (id < box->n_philo)
	{
		box->ph[id].id = id;
		box->ph[id].die = box->tm_die;
		box->ph[id].eat_tm_left = box->n_eat;
		(id == 0) && (box->ph[id].right = &box->ph[box->n_philo - 1].left);
		(id > 0) && (box->ph[id].right = &box->ph[id - 1].left);
		pthread_mutex_init(box->ph[id].right, NULL);
		pthread_mutex_init(&box->ph[id].left, NULL);
		pthread_mutex_init(&box->ph[id].m_die, NULL);
		box->ph[id].box = box;
		id++;
	}
	return (EXIT_SUCCESS);
}

int	init(t_box *box, int *arr, int ac)
{
	box->n_philo = arr[0];
	box->tm_die = arr[1];
	box->tm_eat = arr[2];
	box->tm_sleep = arr[3];
	box->n_eat = NOT;
	(ac == 5) && (box->n_eat = arr[4]);
	pthread_mutex_init(&box->m_start, NULL);
	pthread_mutex_init(&box->m_sttus, NULL);
	pthread_mutex_init(&box->m_endsm, NULL);
	pthread_mutex_init(&box->m_endph, NULL);
	box->ph = malloc(sizeof(t_philo) * box->n_philo);
	box->th = malloc(sizeof(pthread_t) * box->n_philo);
	if (!box->ph || !box->th)
		exit ((printf(R"Error➜"E" memory allocator") * 0) + ERROR);
	init_ph(box);
	init_th(box);
	return (EXIT_SUCCESS);
}
