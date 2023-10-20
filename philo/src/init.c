/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:24:52 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 14:43:26 by dacortes         ###   ########.fr       */
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
	box->philos = malloc(box->n_philo * sizeof(t_philo));
	if (!box->philos)
		return (1);
	box->threads = malloc(box->n_philo * sizeof(pthread_t));
	if (!box->threads)
	{
		free(box->philos);
		return (1);
	}
	ft_init_philos (box);
	ft_init_threads(box);
	return (0);
}

void	ft_init_philos(t_box *box)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&box->m_start);
	while (i < box->n_philo)
	{
		box->philos[i].n_philo = i;
		box->philos[i].die = box->tm_die;
		box->philos[i].eat_times_left = box->n_eat;
		if (i == 0)
			box->philos[i].right
				= &box->philos[box->n_philo - 1].l_fork;
		else
			box->philos[i].right = &box->philos[i - 1].l_fork;
		pthread_mutex_init(box->philos[i].right, NULL);
		pthread_mutex_init(&box->philos[i].l_fork, NULL);
		pthread_mutex_init(&box->philos[i].mutex_die, NULL);
		box->philos[i].box = box;
		i++;
	}
}

void	ft_init_threads(t_box	*box)
{
	int	i;

	i = 0;
	while (i < box->n_philo)
	{
		pthread_create(&box->threads[i], NULL, &life, &box->philos[i]);
		i++;
	}
}
