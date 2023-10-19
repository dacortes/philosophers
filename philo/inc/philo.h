/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:07:41 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/19 10:37:53 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
/******************************************************************************/
/*                            INCLUDES                                        */
/******************************************************************************/

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

/******************************************************************************/
/*                            COLORS                                          */
/******************************************************************************/

# define E "\033[m"        //end
# define R "\033[1;31m"    //red
# define G "\033[1;32m"    //green
# define Y "\033[1;33m"    //yellow
# define B "\033[1;34m"    //blue
# define T "\033[1;35m"	   //Turquesa
# define C "\033[1;36m"    //Cyan
# define O "\033[38;5;208m" //orange
# define F "\033[38;5;128m"  //purple

/******************************************************************************/
/*                            UTILS                                           */
/******************************************************************************/

/* Outputs */
# define NOT	-1
# define ERROR	-1
# define FALSE	0
# define TRUE	1
/*  Status philo */
# define FORK	"\033[1;32mhas taken a fork\033[m"
# define EAT	"\033[1;33mis eating\033[m"
# define SLEEP	"\033[38;5;128mis sleeping\033[m"
# define THINK	"\033[1;32mis thinking\033[m"
# define DIE	"\033[1;31mdied\033[m"

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left;
	pthread_mutex_t	right;
}	t_philo;
/*
	arr[0] = num_philos arr[1] = tm_to_die
	arr[2] = tm_to_eat  arr[3] = tm_to_sleep
	arr[4] = number_of_times_each_philosopher_must_eat 
*/
typedef struct s_box
{
	int			n_philo;
	int			tm_die;
	int			tm_eat;
	int			tm_sleep;
	int			tm_mt_eat;
	t_philo		*ph;
	pthread_t	*th;
}	t_box;

/******************************************************************************/
/*                            FUNTIONS                                        */
/******************************************************************************/

/* src/init.c */
int	init(t_box *box, int *arr, int ac);

/* src/utils.c */
int		ft_atoi(char *str);
int		is_digit(char *str);

/* src/parce.c */
int		check_av(int ac, char **av);
int		get_arg(int ac, char **av, int check, int *array);
#endif