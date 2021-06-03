/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/03 16:47:54 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char *argv[])
{
	t_params	parameters;
	t_philo		*philosophers;

	if (argc != 5 && argc != 6)
		print_error("Error: wrong number of parameters", 2);
	parameters = get_parameters(argv);
	philosophers = init_philo(parameters);
	parameters.philosophers = philosophers;
	parameters.forks = init_forks(parameters);
	parameters = init_parameters(philosophers, parameters);
	int	i = 0;
	pthread_t id;
	while (i < parameters.nb_philo)
	{
		pthread_create(&id, NULL, &philosopher_loop, &philosophers[i]);
		ft_usleep(50);
		if (i + 2 >= parameters.nb_philo && i % 2 == 0)
			i = 1;
		else
			i += 2;
	}
	while (1)
	{
		i = 0;
		while (i < parameters.nb_philo)
		{	
			if (get_timestamp(parameters.philosophers[i].last_eat) > (unsigned long int)parameters.time_die + 10)
			{
				print_die(get_timestamp(parameters.start_time), philosophers[i].id, parameters);
				exit(1);
			}
			i++;
		}
	}
	parameters = clean_parameters(parameters);
}
