/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:02 by user42            #+#    #+#             */
/*   Updated: 2021/06/07 15:31:44 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

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
	int					nb_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	unsigned long int	start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		message;
	t_philo				*philosophers;
}						t_params;

typedef struct s_philo
{
	int					id;
	int					nb_eat;
	unsigned long int	last_eat;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		right_fork;
	t_params			*parameters;
}						t_philo;

/*
** Parsing
*/
t_params			get_parameters(char *argv[]);
int					lil_atoi(const char *str);

/*
** Initialization
*/
t_philo				*init_philo(t_params parameters);
pthread_mutex_t		*init_forks(t_params parameters);


/*
** Philosopher functions
*/
t_params			init_parameters(t_philo *philosophers, t_params params);
void				launch_philosphers(t_philo *philosophers, \
									t_params parameters);
void				*philosopher_loop(void *void_philo);
t_params			clean_parameters(t_params params);
void				*philosopher_monitor(void *void_philosophers);

/*
** Time functions
*/
unsigned long int	get_time(void);
unsigned long int	get_timestamp(unsigned long int old_time);
void				ft_usleep(unsigned long int	time_ms);

/*
** Print message
*/
void				print_eat(unsigned long int timestamp, \
							int philosopher_id, t_params parameters);
void				print_sleep(unsigned long int timestamp, \
							int philosopher_id, t_params parameters);
void				print_think(unsigned long int timestamp, \
							int philosopher_id, t_params parameters);
void				print_die(unsigned long int timestamp, \
							int philosopher_id, t_params parameters);
void				print_fork(unsigned long int timestamp, \
							int philopher_id, t_params parameters);

/*
** Utility
*/
void				print_error(char *message, int exit_code);

#endif
