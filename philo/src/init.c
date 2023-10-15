/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:08:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/15 18:14:19 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init(t_box *bx, int ac)
{
	bx->arr[0] = bx->n_philo;
	bx->arr[1] = bx->tm_die;
	bx->arr[2] = bx->tm_eat;
	bx->arr[3] = bx->n_philo;
	return (EXIT_SUCCESS);
}