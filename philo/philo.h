/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:02 by user42            #+#    #+#             */
/*   Updated: 2021/06/11 09:58:50 by lchapren         ###   ########.fr       */
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
	unsigned long	start_time;
	pthread_mutex_t	message;
	pthread_mutex_t	*forks;
	t_philo			*philosophers;
}					t_params;

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	unsigned long	last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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
pthread_mutex_t	*init_forks(t_params *parameters);

/*
** Philosopher functions
*/
pthread_t		launch_philosphers(t_philo *philosophers, \
									t_params *parameters);
void			*philosopher_loop(void *void_philo);
void			*philosopher_monitor(void *void_philosophers);
int				verify_death(t_philo *philosophers, t_params *parameters, \
							int eating_done);

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
