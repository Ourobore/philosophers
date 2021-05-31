/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/05/31 12:18:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int main(int argc, char *argv[])
{
    t_params    params;

    if (argc != 5 && argc != 6)
        print_error("Error: wrong number of parameters", 2);
    params = get_parameters(argv);
    printf("nb_philo: %d\n", params.nb_philo);
    printf("time_die: %d\n", params.time_die);
    printf("time_eat: %d\n", params.time_eat);
    printf("time_sleep: %d\n", params.time_sleep);
    if (argc == 6)
        printf("nb_eat: %d\n", params.nb_eat);
}