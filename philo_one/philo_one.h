/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:02 by user42            #+#    #+#             */
/*   Updated: 2021/05/31 12:03:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <pthread.h>

typedef struct  s_params
{
    int nb_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int nb_eat;
}   t_params;

/*
** Parsing
*/
t_params    get_parameters(char *argv[]);
int lil_atoi(const char *str);



/*
** Utility
*/
void    print_error(char *message, int exit_code);
