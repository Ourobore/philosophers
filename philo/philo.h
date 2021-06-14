/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:02 by user42            #+#    #+#             */
/*   Updated: 2021/06/14 15:44:41 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_params
{
	int				nb_philo;
	int				nb_eat;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				end_threads;
	unsigned long	start_time;
	pthread_mutex_t	message;
	pthread_mutex_t	end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutexes_eating;
	pthread_mutex_t	*mutexes_nb_eat;
	t_philo			*philosophers;
}					t_params;

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	unsigned long	last_eat;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*eating_lock;
	pthread_mutex_t	*nb_eat_lock;
	t_params		*parameters;
}					t_philo;

/*
** Parsing
*/
int				get_parameters(char *argv[], t_params *parameters);
int				lil_atoi(const char *str);

/*
** Initialization
*/
int				initial_setup(t_philo **philosophers, \
							t_params **parameters, char *argv[]);
int				init_parameters(t_philo *philosophers, t_params *parameters);
int				malloc_mutexes(t_params **parameters);

/*
** Philosopher functions
*/
int				launch_threads(t_philo *philosophers, \
								t_params *parameters, pthread_t *monitor_id);
void			*philosopher_loop(void *void_philo);
void			*philosopher_monitor(void *void_philosophers);

/*
** Time functions
*/
unsigned long	get_time(void);
unsigned long	get_timestamp(unsigned long int old_time);
void			ft_usleep(unsigned long int	time_ms);

/*
** Print message
*/
void			print_fork(int philo_id, t_params *parameters);
void			print_eat(int philo_id, t_params *parameters);
void			print_sleep(int philo_id, t_params *parameters);
void			print_think(int philo_id, t_params *parameters);
void			print_die(int philo_id, t_params *parameters);

/*
** Utility
*/
void			free_structures(t_philo *philosophers, t_params *parameters);

#endif
