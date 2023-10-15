/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:12:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/15 09:37:14 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	status(t_box *bx)
{
	int	tm_die;
	int	i;

	i = 0;
	while (i < bx->n_philo)
	{
		pthread_mutex_lock(&bx->philo[i].mt_tm_die);
		tm_die = bx->philo[i].tm_die;
		pthread_mutex_unlock(&bx->philo[i].mt_tm_die);
		if (tm_elapsed(bx->start) >= tm_die)
		{
			show_ln(&bx->philo[i], DIE);
			pthread_mutex_lock(&bx->sm_end);
			bx->end_of_sm = 1;
			pthread_mutex_unlock(&bx->sm_end);
			break ;
		}
		if (bx->tm_mt_eat > 0 && status_tm_eaten(bx) == 1)
			break ;
		i++;
		(i == bx->n_philo) && (i = 0);
		usleep(100);
	}
}

void	eating_rn(t_philo *aux)
{
	pthread_mutex_lock(&aux->left);
	pthread_mutex_lock(aux->right);
	show_ln(aux, FORK);
	show_ln(aux, FORK);
	pthread_mutex_lock(&aux->mt_tm_die);
	aux->tm_die = tm_elapsed(aux->bx->start) + aux->bx->tm_die;
	pthread_mutex_unlock(&aux->mt_tm_die);
	show_ln(aux, EAT);
	tm_sleep(aux->bx->tm_eat, aux->bx);
	if (aux->bx->tm_mt_eat > 0 && aux->tm_lft_eat > 0)
	{
		aux->tm_lft_eat--;
		if (!aux->tm_lft_eat)
		{
			pthread_mutex_lock(&aux->bx->ph_end);
			aux->bx->end_of_ph++;
			pthread_mutex_unlock(&aux->bx->ph_end);
		}
	}
	pthread_mutex_unlock(&aux->left);
	pthread_mutex_unlock(aux->right);
	show_ln(aux, SLEEP);
	tm_sleep(aux->bx->tm_sleep, aux);
	show_ln(aux, THINK);
}

void	*start_rn(void *ptr)
{
	t_philo	*aux;
	int		end;
	int		i;


	aux = (t_philo *)ptr;
	pthread_mutex_lock(&aux->bx->sm_start);
	pthread_mutex_unlock(&aux->bx->sm_start);
	if ((aux->num) % 2 == 1)
	{
		tm_sleep(1, aux->bx);
		pthread_mutex_lock(&aux->bx->sm_start);
		pthread_mutex_unlock(&aux->bx->sm_start);
	}
	i = 0;
	end = 0;
	while (end != 1)
	{
		if (aux->bx->n_philo != 1)
			eating_rn(aux);
		pthread_mutex_lock(&aux->bx->end_of_sm);
		end = aux->bx->end_of_sm;
		pthread_mutex_unlock(&aux->bx->end_of_sm);
	}
	return ((void *)0);
}
