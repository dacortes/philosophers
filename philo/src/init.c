/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:08:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/19 10:47:59 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*my_test(void *ph)
{
	t_philo	*aux;

	aux = (t_philo *)ph;
	printf("%d\n", aux->id);
	return (NULL);
}

int	init_th(t_box *box)
{
	int	id;

	id = 0;
	while (id < box->n_philo)
	{
		if (pthread_create(&box->th[id], NULL, my_test, &box->ph[id]) != 0)
			exit ((printf(R"Error➜"E" Create threads\n") * 0) + - ERROR);
		id++;
	}	
	return (EXIT_FAILURE);
}

int	init_ph(t_philo **ph, int n_philo)
{
	int	id;

	id = 0;
	while (id < n_philo)
	{
		(*ph)[id].id = id;
		pthread_mutex_init(&(*ph)[id].right, NULL);
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
	box->tm_mt_eat = NOT;
	(ac == 5) && (box->tm_mt_eat = arr[4]);
	box->ph = malloc(sizeof(t_philo) * box->n_philo);
	box->th = malloc(sizeof(pthread_t) * box->n_philo);
	if (!box->ph || !box->th)
		exit ((printf(R"Error➜"E" memory allocator") * 0) + ERROR);
	init_ph(&box->ph, box->n_philo);
	init_th(box);
	return (EXIT_SUCCESS);
}