/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:24:42 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 14:36:08 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_box	box;
	int		arr[5];

	if (get_arg (ac, av, check_av(ac, av), arr) == ERROR)
		return (ERROR);
	if (init(&box, av, (ac - 1)) == ERROR)
		return (ERROR);
	tm_sleep(100, &box);
	gettimeofday(&box.start, NULL);
	pthread_mutex_unlock(&box.m_start);
	supervisor(&box);
	ft_end(&box);
	return (0);
}
