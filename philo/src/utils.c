/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:25:09 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/21 10:27:46 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_time_pass(struct timeval start)
{
	struct timeval	end;
	suseconds_t		tm_passed;

	gettimeofday(&end, NULL);
	tm_passed = (end.tv_usec / 1000 + end.tv_sec * 1000)
		- (start.tv_usec / 1000 + start.tv_sec * 1000);
	return (tm_passed);
}

void	ft_print_line(char *color, t_philo *aux, char *s, int n)
{
	int		i;
	int		game_ended;

	game_ended = 0;
	pthread_mutex_lock(&aux->box->m_print);
	pthread_mutex_lock(&aux->box->m_end);
	game_ended = aux->box->end;
	pthread_mutex_unlock(&aux->box->m_end);
	i = ft_time_pass(aux->box->start);
	if (game_ended != 1 || n == 1)
		printf("%s%d %d %s\n%s", color, i, aux->n_philo + 1, s, E);
	pthread_mutex_unlock(&aux->box->m_print);
}

int	tm_sleep(int millisec, t_box *box)
{
	int	end;

	end = ft_time_pass(box->start) + millisec;
	while (ft_time_pass(box->start) < end)
		usleep(100);
	return (EXIT_SUCCESS);
}

void	ft_end(t_box *box)
{
	int	i;

	i = -1;
	while (++i < box->n_philo)
		pthread_join(box->th[i], NULL);
	i = 0;
	while (i < (box->n_philo))
	{
		pthread_mutex_destroy(&box->ph[i].left);
		pthread_mutex_destroy(&box->ph[i].m_die);
		i++;
	}
	pthread_mutex_destroy(&box->m_end);
	pthread_mutex_destroy(&box->m_print);
	pthread_mutex_destroy(&box->m_start);
	pthread_mutex_destroy(&box->m_end_ph);
	free(box->ph);
	free(box->th);
}
