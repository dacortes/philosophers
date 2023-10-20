/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:18:39 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 14:31:17 by dacortes         ###   ########.fr       */
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
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

/*
	arr[0] = num_philos arr[1] = tm_to_die
	arr[2] = tm_to_eat  arr[3] = tm_to_sleep
	arr[4] = number_of_times_each_philosopher_must_eat 
*/
typedef struct s_philo	t_philo;

typedef struct s_box
{
	int				n_philo;
	int				tm_die;
	int				tm_eat;
	int				tm_dream;
	int				n_eat;
	int				finish;
	int				n_eat_philo;
	struct timeval	t_start;
	struct s_philo	*philos;
	pthread_t		*threads;
	pthread_mutex_t	mprint;
	pthread_mutex_t	mstart;
	pthread_mutex_t	mfinish;
	pthread_mutex_t	philo_finish;
}	t_box;
struct s_philo
{
	int					n_philo;
	int					t_die;
	int					eat_times_left;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		mutex_t_die;
	struct s_box		*main;
};

/* src/parce.c */
int		ft_atoi(char *str);
int		check_av(int ac, char **av);
int		get_arg(int ac, char **av, int check, int *array);

int			ft_box_init(t_box *main, char **args);
void		ft_init_threads(t_box	*main);
long		ft_time_pass(struct timeval t_start);

void		ft_init_philos(t_box *main);
void		*life(void *arg);
void		eating(t_philo *philo);

void		control(t_box *main);
int			control_eat(t_box	*main);
void		ft_finish(t_box	*main);
void		times_eaten(t_philo *philo);

void		ft_print_line(char *color, t_philo *aux, char *s, int n);
int			ft_sleep(int millisec, t_box *main);
int			ft_sleep_start(int millisec, t_box *main);

#endif