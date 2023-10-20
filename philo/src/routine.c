/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:13:28 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 14:31:17 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*life(void *arg)
{
	t_philo	*philo;
	int		stt;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->main->mstart);
	pthread_mutex_unlock(&philo->main->mstart);
	if (philo->n_philo % 2 == 1)
	{
		ft_sleep(50, philo->main);
		pthread_mutex_lock(&philo->main->mstart);
		pthread_mutex_unlock(&philo->main->mstart);
	}
	stt = 0;
	while (stt != 1)
	{
		eating(philo);
		pthread_mutex_lock(&philo->main->mfinish);
		stt = philo->main->finish;
		pthread_mutex_unlock(&philo->main->mfinish);
	}
	return ((void *) 0);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	ft_print_line(G, philo, FORK, 0);
	if (philo->main->n_philo == 1)
	{
		while (philo->main->finish == 0)
			ft_sleep(1, philo->main);
		exit(1);
	}
	pthread_mutex_lock(philo->r_fork);
	ft_print_line(G, philo, FORK, 0);
	pthread_mutex_lock(&philo->mutex_t_die);
	philo->t_die = ft_time_pass(philo->main->t_start) + philo->main->tm_die;
	pthread_mutex_unlock(&philo->mutex_t_die);
	if (philo->eat_times_left != 0)
		ft_print_line(Y, philo, EAT, 0);
	times_eaten(philo);
	ft_sleep(philo->main->tm_eat, philo->main);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->eat_times_left != 0)
		ft_print_line(B, philo, SLEEP, 0);
	ft_sleep(philo->main->tm_dream, philo->main);
	if (philo->eat_times_left != 0)
		ft_print_line(O, philo, THINK, 0);
}

void	control(t_box *main)
{
	int	i;
	int	time;

	i = 0;
	while (i < main->n_philo)
	{
		pthread_mutex_lock(&main->philos[i].mutex_t_die);
		time = main->philos[i].t_die;
		pthread_mutex_unlock(&main->philos[i].mutex_t_die);
		if (ft_time_pass(main->t_start) > time)
		{
			pthread_mutex_lock(&main->mfinish);
			main->finish = 1;
			pthread_mutex_unlock(&main->mfinish);
			ft_print_line(R, &main->philos[i], DEAD, 1);
			break ;
		}
		if (main->n_eat > 0 && control_eat(main) == 1)
			break ;
		i++;
		if (i == main->n_philo)
			i = 0;
		usleep(60);
	}
}

void	times_eaten(t_philo *philo)
{
	if (philo->main->n_eat >= philo->eat_times_left
		&& philo->eat_times_left >= 0)
	{
		philo->eat_times_left--;
		if (philo->eat_times_left == 0)
		{
			pthread_mutex_lock(&philo->main->philo_finish);
			philo->main->n_eat_philo++;
			pthread_mutex_unlock(&philo->main->philo_finish);
		}
	}
}

int	control_eat(t_box	*main)
{
	int	i;
	int	aux;

	i = 0;
	pthread_mutex_lock(&main->philo_finish);
	aux = main->n_eat_philo;
	pthread_mutex_unlock(&main->philo_finish);
	if (aux == main->n_philo)
	{
		pthread_mutex_lock(&main->mfinish);
		main->finish = 1;
		pthread_mutex_unlock(&main->mfinish);
		ft_print_line(R, &main->philos[i], "ha terminado", 1);
		return (1);
	}
	return (0);
}
