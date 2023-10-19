/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:21:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/19 14:32:44 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	end_sm(t_box *box)
{
	int	id;

	id  = 0;
	while (id < box->n_philo)
	{
		pthread_mutex_destroy(&box->ph[id].left);
		id++;
	}
	if (box->ph)
		free(box->ph);
	if (box->th)
		free(box->th);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_box	box;
	int		arr[5];

	get_arg (ac, av, check_av(ac, av), arr);
	init(&box, arr, (ac - 1));
	end_sm(&box);
	return (EXIT_SUCCESS);
}
