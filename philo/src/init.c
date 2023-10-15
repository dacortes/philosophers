/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:08:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/15 11:05:06 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ph_init(t_box *bx)
{
	int	i;

	i = 0;
	while (i < (bx->n_philo))
	{
		bx->philo[i].num = i;
		bx->philo[i].tm_die = bx->tm_die;
		bx->philo[i].tm_lft_eat = bx->tm_mt_eat;
		pthread_mutex_init(&bx->philo[i].left, NULL);
		(i == 0) && (bx->philo[i].right = &bx->philo[bx->n_philo - 1].left);
		(i > 0) && (bx->philo[i].right = &bx->philo[i - 1].left);
		pthread_mutex_init(&bx->philo[i].mt_tm_die, NULL);
		bx->philo[i].bx = bx;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	th_init(t_box *bx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (bx->n_philo))
	{
		j = i;
		if (pthread_create(&bx->th[j], NULL, &start_rn, bx->th[j]) != 0)
			return ((printf(R"Error➜"E" create threads") * 0) + TRUE);
		i++;
	}
	return (EXIT_SUCCESS);
}

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
	pthread_mutex_init(&bx->sm_end, NULL);
	pthread_mutex_init(&bx->ph_end, NULL);
	pthread_mutex_lock(&bx->sm_start);
	gettimeofday(&bx->start, NULL);
	ph_init(bx);
	th_init(bx);
	return (EXIT_SUCCESS);
}
