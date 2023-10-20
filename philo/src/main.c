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

	get_arg (ac, av, check_av(ac, av), arr);
	if (ft_box_init(&box, av) != 0)
		return (1);
	ft_sleep(100, &box);
	gettimeofday(&box.start, NULL);
	pthread_mutex_unlock(&box.m_start);
	control(&box);
	ft_end(&box);
	return (0);
}
