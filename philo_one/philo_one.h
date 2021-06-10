/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:02 by user42            #+#    #+#             */
/*   Updated: 2021/06/10 12:12:11 by lchapren         ###   ########.fr       */
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
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	t_philo			*philosophers;
}						t_params;

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	unsigned long	last_eat;
	int				end_thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*message;
	t_params		*parameters;
}						t_philo;

/*
** Parsing
*/
t_params		get_parameters(char *argv[]);
int				lil_atoi(const char *str);

/*
** Initialization
*/
t_philo			*init_philo(t_params parameters);
pthread_mutex_t	*init_forks(t_params parameters);


/*
** Philosopher functions
*/
t_params		init_parameters(t_philo *philosophers, t_params params);
pthread_t		launch_philosphers(t_philo *philosophers, \
									t_params parameters);
void			*philosopher_loop(void *void_philo);
void			clean_parameters(t_philo *philosophers, \
									t_params parameters);
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
void			print_fork(t_philo philosopher, t_params parameters);
void			print_eat(t_philo philosopher, t_params parameters);
void			print_sleep(t_philo philosopher, t_params parameters);
void			print_think(t_philo philosopher, t_params parameters);
void			print_die(t_philo philosopher, t_params parameters);

/*
** Utility
*/
void			print_error(char *message, int exit_code);

#endif
