/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:24:52 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 14:31:17 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_box_init(t_box *main, char **args)
{
	main->finish = 0;
	main->n_eat_philo = 0;
	main->n_philo = ft_atoi(args[1]);
	main->tm_die = ft_atoi(args[2]);
	main->tm_eat = ft_atoi(args[3]);
	main->tm_dream = ft_atoi(args[4]);
	main->n_eat = -1;
	if (args[5])
		main->n_eat = ft_atoi(args[5]);
	pthread_mutex_init(&main->mstart, NULL);
	pthread_mutex_init(&main->mfinish, NULL);
	pthread_mutex_init(&main->philo_finish, NULL);
	pthread_mutex_init(&main->mprint, NULL);
	main->philos = malloc(main->n_philo * sizeof(t_philo));
	if (!main->philos)
		return (1);
	main->threads = malloc(main->n_philo * sizeof(pthread_t));
	if (!main->threads)
	{
		free(main->philos);
		return (1);
	}
	ft_init_philos (main);
	ft_init_threads(main);
	return (0);
}

void	ft_init_philos(t_box *main)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&main->mstart);
	while (i < main->n_philo)
	{
		main->philos[i].n_philo = i;
		main->philos[i].t_die = main->tm_die;
		main->philos[i].eat_times_left = main->n_eat;
		if (i == 0)
			main->philos[i].r_fork
				= &main->philos[main->n_philo - 1].l_fork;
		else
			main->philos[i].r_fork = &main->philos[i - 1].l_fork;
		pthread_mutex_init(main->philos[i].r_fork, NULL);
		pthread_mutex_init(&main->philos[i].l_fork, NULL);
		pthread_mutex_init(&main->philos[i].mutex_t_die, NULL);
		main->philos[i].main = main;
		i++;
	}
}

void	ft_init_threads(t_box	*main)
{
	int	i;

	i = 0;
	while (i < main->n_philo)
	{
		pthread_create(&main->threads[i], NULL, &life, &main->philos[i]);
		i++;
	}
}
