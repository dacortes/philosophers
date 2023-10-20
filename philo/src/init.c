/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:24:52 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 14:54:27 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_box_init(t_box *box, char **args)
{
	box->end = 0;
	box->eat_n_ph = 0;
	box->n_philo = ft_atoi(args[1]);
	box->tm_die = ft_atoi(args[2]);
	box->tm_eat = ft_atoi(args[3]);
	box->tm_dream = ft_atoi(args[4]);
	box->n_eat = -1;
	if (args[5])
		box->n_eat = ft_atoi(args[5]);
	pthread_mutex_init(&box->m_start, NULL);
	pthread_mutex_init(&box->m_end, NULL);
	pthread_mutex_init(&box->m_end_ph, NULL);
	pthread_mutex_init(&box->m_print, NULL);
	box->ph = malloc(box->n_philo * sizeof(t_philo));
	if (!box->ph)
		return (1);
	box->threads = malloc(box->n_philo * sizeof(pthread_t));
	if (!box->threads)
	{
		free(box->ph);
		return (1);
	}
	ft_init_ph (box);
	ft_init_threads(box);
	return (0);
}

void	ft_init_ph(t_box *box)
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
		pthread_mutex_init(&box->ph[i].mutex_die, NULL);
		box->ph[i].box = box;
		i++;
	}
}

void	ft_init_threads(t_box	*box)
{
	int	i;

	i = 0;
	while (i < box->n_philo)
	{
		pthread_create(&box->threads[i], NULL, &life, &box->ph[i]);
		i++;
	}
}
