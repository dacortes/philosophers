/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:12:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/19 15:41:32 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->left);
}

void	*run(void *ph)
{
	t_philo	*aux;
	int		stt;

	aux = (t_philo *)ph;
	pthread_mutex_lock(&aux->box->m_start);
	pthread_mutex_unlock(&aux->box->m_start);
	if (aux->id % 2 == 1)
	{
		tm_sleep(aux->box, 50);
		pthread_mutex_lock(&aux->box->m_start);
		pthread_mutex_unlock(&aux->box->m_start);
	}
	stt = 0;
	while (stt != 1)
	{
		eating(aux);
		pthread_mutex_lock(&aux->box->m_endsm);
		stt = aux->box->end;
		pthread_mutex_unlock(&aux->box->m_endsm);
	}
	printf("philo: %d time_die: %d\n", (aux->id + 1), aux->die);
	return (NULL);
}
