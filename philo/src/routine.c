/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:13:28 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 14:43:26 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*life(void *arg)
{
	t_philo	*philo;
	int		stt;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->box->m_start);
	pthread_mutex_unlock(&philo->box->m_start);
	if (philo->n_philo % 2 == 1)
	{
		ft_sleep(50, philo->box);
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
	return ((void *) 0);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	ft_print_line(G, philo, FORK, 0);
	if (philo->box->n_philo == 1)
	{
		while (philo->box->end == 0)
			ft_sleep(1, philo->box);
		exit(1);
	}
	pthread_mutex_lock(philo->right);
	ft_print_line(G, philo, FORK, 0);
	pthread_mutex_lock(&philo->mutex_die);
	philo->die = ft_time_pass(philo->box->start) + philo->box->tm_die;
	pthread_mutex_unlock(&philo->mutex_die);
	if (philo->eat_times_left != 0)
		ft_print_line(Y, philo, EAT, 0);
	times_eaten(philo);
	ft_sleep(philo->box->tm_eat, philo->box);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->right);
	if (philo->eat_times_left != 0)
		ft_print_line(B, philo, SLEEP, 0);
	ft_sleep(philo->box->tm_dream, philo->box);
	if (philo->eat_times_left != 0)
		ft_print_line(O, philo, THINK, 0);
}

void	control(t_box *box)
{
	int	i;
	int	time;

	i = 0;
	while (i < box->n_philo)
	{
		pthread_mutex_lock(&box->philos[i].mutex_die);
		time = box->philos[i].die;
		pthread_mutex_unlock(&box->philos[i].mutex_die);
		if (ft_time_pass(box->start) > time)
		{
			pthread_mutex_lock(&box->m_end);
			box->end = 1;
			pthread_mutex_unlock(&box->m_end);
			ft_print_line(R, &box->philos[i], DEAD, 1);
			break ;
		}
		if (box->n_eat > 0 && control_eat(box) == 1)
			break ;
		i++;
		if (i == box->n_philo)
			i = 0;
		usleep(60);
	}
}

void	times_eaten(t_philo *philo)
{
	if (philo->box->n_eat >= philo->eat_times_left
		&& philo->eat_times_left >= 0)
	{
		philo->eat_times_left--;
		if (philo->eat_times_left == 0)
		{
			pthread_mutex_lock(&philo->box->m_end_ph);
			philo->box->eat_n_ph++;
			pthread_mutex_unlock(&philo->box->m_end_ph);
		}
	}
}

int	control_eat(t_box	*box)
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
		ft_print_line(R, &box->philos[i], "ha terminado", 1);
		return (1);
	}
	return (0);
}
