/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:07:41 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/20 11:21:31 by dacortes         ###   ########.fr       */
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

/*
	arr[0] = num_philos arr[1] = tm_to_die
	arr[2] = tm_to_eat  arr[3] = tm_to_sleep
	arr[4] = number_of_times_each_philosopher_must_eat 
*/
typedef struct s_philo t_philo;

typedef struct s_box
{
	int				n_philo;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				n_eat;
	int				eat_n_ph;
	int				end;
	struct timeval	start;
	struct s_philo	*ph;
	pthread_t		*th;
	pthread_mutex_t m_start;
	pthread_mutex_t	m_sttus;
	pthread_mutex_t	m_endsm;
	pthread_mutex_t	m_endph;
}	t_box;

struct s_philo
{
	int				id;
	int				die;
	int				eat_tm_left;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
	pthread_mutex_t	m_die;
	t_box			*box;
};

/******************************************************************************/
/*                            FUNTIONS                                        */
/******************************************************************************/

/* src/init.c */
int		init(t_box *box, int *arr, int ac);

/* src/parce.c */
int		check_av(int ac, char **av);
int		get_arg(int ac, char **av, int check, int *array);

/* src/rutine.c */
void	*run(void *ph);
void	eating(t_philo *ph);
void	supervisor(t_box *box);

/* src/utils.c */
int		ft_atoi(char *str);
int		is_digit(char *str);
int		time_elapsed(struct timeval start);
int		tm_sleep(t_box *box, int millisec);
int		show_stt(t_philo *ph, char *str, int stt);
#endif