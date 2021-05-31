/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 13:16:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/05/31 13:16:21 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

t_params    get_parameters(char *argv[])
{
    int i;
    int value;
    t_params params;

    i = 1;
    while (argv[i])
    {
        value = 0;
        value = lil_atoi(argv[i]);
        if (value == -1)
            print_error("Error: parameter not valid", 3);
        if (i == 1)
            params.nb_philo = value;
        else if (i == 2)
            params.time_die = value;
        else if (i == 3)
            params.time_eat = value;
        else if (i == 4)
            params.time_sleep = value;
        else if (i == 5)
            params.nb_eat = value;
        i++;
    }
    return (params);
}