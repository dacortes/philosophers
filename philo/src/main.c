/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:24:42 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 14:26:57 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_box	main;
	int		arr[5];

	get_arg (ac, av, check_av(ac, av), arr);
	if (ft_box_init(&main, av) != 0)
		return (1);
	ft_sleep(100, &main);
	gettimeofday(&main.t_start, NULL);
	pthread_mutex_unlock(&main.mstart);
	control(&main);
	ft_finish(&main);
	return (0);
}
