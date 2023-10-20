/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:25:09 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 14:28:06 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_time_pass(struct timeval t_start)
{
	struct timeval	tm_end;
	suseconds_t		tm_passed;

	gettimeofday(&tm_end, NULL);
	tm_passed = (tm_end.tv_usec / 1000 + tm_end.tv_sec * 1000)
		- (t_start.tv_usec / 1000 + t_start.tv_sec * 1000);
	return (tm_passed);
}

void	ft_print_line(char *color, t_philo *aux, char *s, int n)
{
	int		i;
	int		game_finished;

	game_finished = 0;
	pthread_mutex_lock(&aux->main->mprint);
	pthread_mutex_lock(&aux->main->mfinish);
	game_finished = aux->main->finish;
	pthread_mutex_unlock(&aux->main->mfinish);
	i = ft_time_pass(aux->main->t_start);
	if (game_finished != 1 || n == 1)
		printf("%s%d %d %s\n%s", color, i, aux->n_philo + 1, s, E);
	pthread_mutex_unlock(&aux->main->mprint);
}

int	ft_sleep(int millisec, t_box *main)
{
	int	tm_end;

	tm_end = ft_time_pass(main->t_start) + millisec;
	while (ft_time_pass(main->t_start) < tm_end)
		usleep(100);
	return (0);
}

void	ft_finish(t_box *main)
{
	int	i;

	i = -1;
	while (++i < main->n_philo)
		pthread_join(main->threads[i], NULL);
	i = 0;
	while (i < (main->n_philo))
	{
		pthread_mutex_destroy(&main->philos[i].l_fork);
		pthread_mutex_destroy(&main->philos[i].mutex_t_die);
		i++;
	}
	pthread_mutex_destroy(&main->mfinish);
	pthread_mutex_destroy(&main->mprint);
	pthread_mutex_destroy(&main->mstart);
	pthread_mutex_destroy(&main->philo_finish);
	free(main->philos);
	free(main->threads);
}
