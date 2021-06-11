/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/11 10:00:36 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (!init_parameters(philosophers, parameters))
		return (1);
	monitor_id = launch_philosphers(philosophers, parameters);
	pthread_join(monitor_id, NULL);
	free_structures(philosophers, parameters);
	return (0);
}
