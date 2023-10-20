/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:12:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 12:30:17 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	times_eaten(t_philo *ph)
{
	if (ph->box->n_eat >= ph->eat_tm_left && ph->eat_tm_left >= 0)
	{
		ph->eat_tm_left--;
		if (!ph->eat_tm_left)
		{
			pthread_mutex_lock(&ph->box->m_endph);
			ph->box->eat_n_ph++;
			pthread_mutex_unlock(&ph->box->m_endph);
		}
	}
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->left);
	show_stt(ph, FORK, 0);
	if (ph->box->n_philo == 1)
	{
		while (ph->box->end == 0)
			tm_sleep(ph->box, 1);
		exit (TRUE);
	}
	pthread_mutex_lock(ph->right);
	show_stt(ph, FORK, 0);
	pthread_mutex_lock(&ph->m_die);
	ph->die = time_elapsed((ph->box->start)) + ph->box->tm_die;
	pthread_mutex_unlock(&ph->m_die);
	if (ph->eat_tm_left != 0)
		show_stt(ph, EAT, 0);
	times_eaten(ph);
	tm_sleep(ph->box, ph->box->tm_eat);
	pthread_mutex_lock(&ph->left);
	pthread_mutex_lock(ph->right);
	if (ph->eat_tm_left != 0)
		show_stt(ph, SLEEP, 0);
	tm_sleep(ph->box, ph->box->tm_sleep);
	if (ph->eat_tm_left != 0)
		show_stt(ph, THINK, 0);
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
	return (NULL);
}

static int	supervisor_eat(t_box *box)
{
	int	n_eat;
	int	end;

	end = 0;
	pthread_mutex_lock(&box->m_endph);
	n_eat = box->eat_n_ph;
	pthread_mutex_unlock(&box->m_endph);
	if (n_eat == box->n_philo)
	{
		pthread_mutex_lock(&box->m_endsm);
		box->end = 1;
		pthread_mutex_unlock(&box->m_endsm);
		show_stt(&box->ph[end], "end", 1);
		return (TRUE);
	}
	return (EXIT_SUCCESS);
}

void	supervisor(t_box *box)
{
	int	id;
	int	tm;

	id = 0;
	while (id < box->n_philo)
	{
		pthread_mutex_lock(&box->ph[id].m_die);
		tm = box->ph[id].die;
		pthread_mutex_unlock(&box->ph[id].m_die);
		if (time_elapsed(box->start) > tm)
		{
			pthread_mutex_lock(&box->m_endsm);
			box->end = 1;
			pthread_mutex_unlock(&box->m_endsm);
			show_stt(&box->ph[id], DIE, 1);
			break ;
		}
		if (box->n_eat > 0 && supervisor_eat(box))
			break ;
		id++;
		if (id == box->n_philo)
			id = 0;
		usleep(60);
	}
}
