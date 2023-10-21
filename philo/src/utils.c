/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:25:09 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/21 10:40:41 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	time_elapsed(struct timeval start)
{
	struct timeval	end;
	suseconds_t		pass;

	gettimeofday(&end, NULL);
	pass = (end.tv_usec / 1000 + end.tv_sec * 1000)
		- (start.tv_usec / 1000 + start.tv_sec * 1000);
	return (pass);
}

void	show_stt(char *color, t_philo *ph, char *str, int stt)
{
	int		tm;
	int		end;

	end = 0;
	pthread_mutex_lock(&ph->box->m_print);
	pthread_mutex_lock(&ph->box->m_end);
	end = ph->box->end;
	pthread_mutex_unlock(&ph->box->m_end);
	tm = time_elapsed(ph->box->start);
	if (end != 1 || stt == 1)
		printf("%s%d %d %s\n%s", color, tm, ph->n_philo + 1, str, E);
	pthread_mutex_unlock(&ph->box->m_print);
}

int	tm_sleep(int millisec, t_box *box)
{
	int	end;

	end = time_elapsed(box->start) + millisec;
	while (time_elapsed(box->start) < end)
		usleep(100);
	return (EXIT_SUCCESS);
}

void	ft_end(t_box *box)
{
	int	id;

	id = -1;
	while (++id < box->n_philo)
		pthread_join(box->th[id], NULL);
	id = 0;
	while (id < (box->n_philo))
	{
		pthread_mutex_destroy(&box->ph[id].left);
		pthread_mutex_destroy(&box->ph[id].m_die);
		id++;
	}
	pthread_mutex_destroy(&box->m_end);
	pthread_mutex_destroy(&box->m_print);
	pthread_mutex_destroy(&box->m_start);
	pthread_mutex_destroy(&box->m_end_ph);
	if (box->ph)
		free(box->ph);
	if (box->th)
		free(box->th);
}
