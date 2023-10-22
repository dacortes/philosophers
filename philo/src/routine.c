/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:13:28 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/22 09:38:27 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	times_eaten(t_philo *philo)
{
	if (philo->box->n_eat >= philo->eat_tm_left
		&& philo->eat_tm_left >= 0)
	{
		philo->eat_tm_left--;
		if (philo->eat_tm_left == 0)
		{
			pthread_mutex_lock(&philo->box->m_end_ph);
			philo->box->eat_n_ph++;
			pthread_mutex_unlock(&philo->box->m_end_ph);
		}
	}
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	show_stt(philo, FORK, 0);
	if (philo->box->n_philo == 1)
	{
		tm_sleep(philo->box->tm_die + 10, philo->box);
		pthread_mutex_unlock(&philo->left);
		return ;
	}
	pthread_mutex_lock(philo->right);
	show_stt(philo, FORK, 0);
	pthread_mutex_lock(&philo->m_die);
	philo->die = time_elapsed(philo->box->start) + philo->box->tm_die;
	pthread_mutex_unlock(&philo->m_die);
	if (philo->eat_tm_left != 0)
		show_stt(philo, EAT, 0);
	times_eaten(philo);
	tm_sleep(philo->box->tm_eat, philo->box);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(philo->right);
	if (philo->eat_tm_left != 0)
		show_stt(philo, SLEEP, 0);
	tm_sleep(philo->box->tm_dream, philo->box);
	if (philo->eat_tm_left != 0)
		show_stt(philo, THINK, 0);
}

void	*run(void *ph)
{
	t_philo	*philo;
	int		stt;

	philo = (t_philo *) ph;
	pthread_mutex_lock(&philo->box->m_start);
	pthread_mutex_unlock(&philo->box->m_start);
	if (philo->n_philo % 2 == 1)
	{
		tm_sleep(50, philo->box);
		pthread_mutex_lock(&philo->box->m_start);
		pthread_mutex_unlock(&philo->box->m_start);
	}
	stt = 0;
	while (stt != 1)
	{
		eating(philo);
		pthread_mutex_lock(&philo->box->m_end);
		stt = philo->box->end;
		pthread_mutex_unlock(&philo->box->m_end);
	}
	return (NULL);
}

static int	supervisor_eat(t_box	*box)
{
	int	i;
	int	aux;

	i = 0;
	pthread_mutex_lock(&box->m_end_ph);
	aux = box->eat_n_ph;
	pthread_mutex_unlock(&box->m_end_ph);
	if (aux == box->n_philo)
	{
		pthread_mutex_lock(&box->m_end);
		box->end = 1;
		pthread_mutex_unlock(&box->m_end);
		show_stt(&box->ph[i], "end the simulation", 1);
		return (TRUE);
	}
	return (EXIT_SUCCESS);
}

void	supervisor(t_box *box)
{
	int	id;
	int	time;

	id = 0;
	while (id < box->n_philo)
	{
		pthread_mutex_lock(&box->ph[id].m_die);
		time = box->ph[id].die;
		pthread_mutex_unlock(&box->ph[id].m_die);
		if (time_elapsed(box->start) > time)
		{
			pthread_mutex_lock(&box->m_end);
			box->end = 1;
			pthread_mutex_unlock(&box->m_end);
			show_stt(&box->ph[id], DEAD, 1);
			break ;
		}
		if (box->n_eat > 0 && supervisor_eat(box) == 1)
			break ;
		id++;
		if (id == box->n_philo)
			id = 0;
		usleep(60);
	}
}
