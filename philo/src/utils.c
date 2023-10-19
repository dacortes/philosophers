/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:06:38 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/19 16:28:29 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *str)
{
	long int	num;
	int			sig;
	int			i;

	num = 0;
	sig = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		sig = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			break ;
		num = num * 10 + str[i] - 48;
		i++;
	}
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	return (num * sig);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	time_elapsed(struct timeval start)
{
	struct timeval	end;
	suseconds_t		pass_tm;

	gettimeofday(&end, NULL);
	pass_tm = (end.tv_usec / 1000 + end.tv_sec * 1000)
		- (start.tv_usec / 1000 + start.tv_sec * 1000);
	return (pass_tm);
}

int	tm_sleep(t_box *box, int millisec)
{
	int	end;

	end = time_elapsed(box->start) + millisec;
	while (time_elapsed(box->start) < end)
		usleep(100);
	return (EXIT_SUCCESS);
}

int	show_stt(t_philo *ph, char *str, int stt)
{
	int	tm;
	int end;

	end = 0;
	pthread_mutex_lock(&ph->box->m_sttus);
	pthread_mutex_lock(&ph->box->m_endsm);
	end = ph->box->end;
	pthread_mutex_unlock(&ph->box->m_endsm);
	tm = time_elapsed(ph->box->start);
	if (end != 1 || stt == 1)
		printf("%d %d %s\n", tm, (ph->id + 1), str);
	pthread_mutex_unlock(&ph->box->m_sttus);
	return (EXIT_SUCCESS);
}
