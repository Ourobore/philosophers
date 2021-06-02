/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:02 by user42            #+#    #+#             */
/*   Updated: 2021/06/02 16:44:34 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo t_philo;

typedef struct  s_params
{
    int nb_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int nb_eat;
	unsigned long int	start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t	message;
	t_philo	*philo;
}   t_params;

typedef struct  s_philo
{
	int	id;
    unsigned long int last_eat;
    int nb_eat;
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	t_params	*params;
}   t_philo;

/*
** Parsing
*/
t_params    get_parameters(char *argv[]);
int lil_atoi(const char *str);

/*
** Time functions
*/
unsigned long int	get_time();
unsigned long int	get_timestamp(unsigned long int old_time);

/*
** Print message
*/
void	print_eat(unsigned long int timestamp, int philo_id, t_params params);
void	print_sleep(unsigned long int timestamp, int philo_id, t_params params);
void	print_think(unsigned long int timestamp, int philo_id, t_params params);
void	print_die(unsigned long int timestamp, int philo_id, t_params params);
void	print_fork(unsigned long int timestamp, int philo_id, t_params params);


/*
** Utility
*/
void    print_error(char *message, int exit_code);
