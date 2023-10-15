/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:21:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/15 18:06:41 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_box bx;

	get_arg (ac, av, check_av(ac, av), bx.arr);
	printf("%d\n", bx.n_philo);
	printf("%d\n", bx.tm_die);
	printf("%d\n", bx.tm_eat);
	printf("%d\n", bx.tm_sleep);
	return (EXIT_SUCCESS);
}
