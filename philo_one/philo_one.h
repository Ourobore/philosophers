/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:02 by user42            #+#    #+#             */
/*   Updated: 2021/06/01 11:52:50 by lchapren         ###   ########.fr       */
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
	int	start_time;
	pthread_mutex_t *forks;
	t_philo	*philo;
}   t_params;

typedef struct  s_philo
{
	int	id;
    unsigned long int last_eat;
    int nb_eat;
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
}   t_philo;

/*
** Parsing
*/
t_params    get_parameters(char *argv[]);
int lil_atoi(const char *str);



/*
** Utility
*/
void    print_error(char *message, int exit_code);
