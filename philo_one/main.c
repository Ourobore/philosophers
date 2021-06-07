/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/07 16:39:31 by lchapren         ###   ########.fr       */
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
	launch_philosphers(philosophers, parameters);
	//pthread_t	id;
	//if (pthread_create(&id, NULL, &philosopher_monitor, &philosophers) != 0)
	//	print_error("Error: thread creation failed", 8);
	//while (1)
	//{	
	//}
	//usleep(1000);
	//pthread_mutex_lock(parameters.end_lock);
	//pthread_mutex_unlock(parameters.end_lock);

	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < parameters.nb_philo)
		{	
			if (get_timestamp(parameters.philosophers[i].last_eat) > (unsigned long int)parameters.time_die + 10)
			{
				//printf("prout\n");
				print_die(get_timestamp(parameters.start_time), philosophers[i].id, parameters);
				exit(1);
			}
			i++;
		}
		usleep(1000);
	}
	//parameters = clean_parameters(parameters);
}
