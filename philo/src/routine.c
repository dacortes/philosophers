/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:12:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/14 18:02:09 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	eating_rn(t_philo *aux)
{
	pthread_mutex_lock(&aux->left);
	pthread_mutex_lock(aux->right);
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
