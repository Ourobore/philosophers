/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/10 17:02:45 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	initial_setup(t_philo **philosophers, t_params **parameters, char *argv[])
{
	*parameters = malloc(sizeof(t_params) * 1);
	if (!*parameters)
	{
		printf("Error: malloc failed\n");
		return (0);
	}
	if (!get_parameters(argv, *parameters))
	{
		printf("Error: invalid argument\n");
		free(*parameters);
		return (0);
	}
	*philosophers = malloc(sizeof(t_philo) * (*parameters)->nb_philo);
	if (!*philosophers)
	{
		printf("Error: malloc failed\n");
		free(*parameters);
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	pthread_t	monitor_id;
	t_philo		*philosophers;
	t_params	*parameters;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of parameters\n");
		return (1);
	}
	philosophers = NULL;
	parameters = NULL;
	if (!initial_setup(&philosophers, &parameters, argv))
		return (1);
	parameters->philosophers = philosophers;
	philosophers->parameters = parameters;
	parameters->forks = init_forks(parameters);
	if (!parameters->forks)
	{
		free_structures(philosophers, parameters);
		return (1);
	}
	init_parameters(philosophers, parameters);
	monitor_id = launch_philosphers(philosophers, *philosophers->parameters);
	pthread_join(monitor_id, NULL);
	clean_parameters(philosophers, *philosophers->parameters);
}
