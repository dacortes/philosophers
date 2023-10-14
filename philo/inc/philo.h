/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:07:41 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/14 18:12:48 by dacortes         ###   ########.fr       */
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

typedef struct s_box			t_box;
typedef struct s_philo			t_philo;

struct s_philo
{
	int				num;
	int				tm_die;
	int				tm_lft_eat;
	t_box			*bx;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
	pthread_mutex_t	mt_tm_die;
};
/*
	arr[0] = num_philos arr[1] = tm_to_die
	arr[2] = tm_to_eat  arr[3] = tm_to_sleep
	arr[4] = number_of_times_each_philosopher_must_eat 
*/
struct s_box
{
	int				arr[5];
	int				n_philo;
	int				tm_sleep;
	int				tm_die;
	int				tm_eat;
	int				tm_mt_eat;
	int				end_of_sm;
	int				end_of_ph;
	struct timeval	start;
	t_philo			*philo;
	pthread_t		*th;
	pthread_mutex_t	mt_print;
	pthread_mutex_t	sm_start;
	pthread_mutex_t	sm_end;
	pthread_mutex_t	ph_end;
};

/******************************************************************************/
/*                            FUNTIONS                                        */
/******************************************************************************/

/* src/init.c */
int		init(t_box *bx, int ac);

/* src/main.c*/
void	show_ln(t_philo *ph, char *str);

/* src/utils.c */
int		ft_atoi(char *str);
int		is_digit(char *str);
int		tm_elapsed(struct timeval start);
int		tm_sleep(int mllsec, t_box *bx);

/* src/routune.c  */
void	*start_rn(void *ptr);

/* src/parce.c */
int		check_av(int ac, char **av);
int		get_arg(int ac, char **av, int check, int *array);
#endif