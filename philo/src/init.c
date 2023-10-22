/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:24:52 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/22 10:05:44 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_ph(t_box *box)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&box->m_start);
	while (i < box->n_philo)
	{
		box->ph[i].n_philo = i;
		box->ph[i].die = box->tm_die;
		box->ph[i].eat_tm_left = box->n_eat;
		if (i == 0)
			box->ph[i].right
				= &box->ph[box->n_philo - 1].left;
		else
			box->ph[i].right = &box->ph[i - 1].left;
		pthread_mutex_init(box->ph[i].right, NULL);
		pthread_mutex_init(&box->ph[i].left, NULL);
		pthread_mutex_init(&box->ph[i].m_die, NULL);
		box->ph[i].box = box;
		i++;
	}
}

static int	init_th(t_box	*box)
{
	int	i;

	i = 0;
	while (i < box->n_philo)
	{
		if (pthread_create(&box->th[i], NULL, &run, &box->ph[i]) != 0)
			return ((printf(R"Error➜"E" Create threads\n") * 0) + ERROR);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init(t_box *box, char **arr, int ac)
{
	box->end = 0;
	box->eat_n_ph = 0;
	box->n_philo = ft_atoi(arr[1]);
	box->tm_die = ft_atoi(arr[2]);
	box->tm_eat = ft_atoi(arr[3]);
	box->tm_dream = ft_atoi(arr[4]);
	box->n_eat = NOT;
	(ac == 5) && (box->n_eat = ft_atoi(arr[5]));
	pthread_mutex_init(&box->m_start, NULL);
	pthread_mutex_init(&box->m_end, NULL);
	pthread_mutex_init(&box->m_end_ph, NULL);
	pthread_mutex_init(&box->m_print, NULL);
	box->ph = malloc(box->n_philo * sizeof(t_philo));
	box->th = malloc(box->n_philo * sizeof(pthread_t));
	if (!box->ph || !box->th)
		return ((printf(R"Error➜"E" memory allocator") * 0)
			+ clear_sm(&box->ph, &box->th, ERROR));
	init_ph(box);
	if (init_th(box) == ERROR)
		return (clear_sm(&box->ph, &box->th, ERROR));
	return (EXIT_SUCCESS);
}

int	clear_sm(t_philo **ph, pthread_t **th, int stt)
{
	if (ph && *ph)
	{
		free (*ph);
		*ph = NULL;
	}
	if (th && *th)
	{
		free (*th);
		*th = NULL;
	}
	return (stt);
}
