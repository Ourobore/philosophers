/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/19 10:02:29 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wrong_nb_arguments(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of parameters\n");
		return (1);
	}
	return (0);
}

void	join_threads(t_philo *philosophers, t_params *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->nb_philo)
	{
		pthread_join(philosophers[i].thread_id, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pthread_t	monitor_id;
	t_philo		*philosophers;
	t_params	*parameters;

	if (wrong_nb_arguments(argc))
		return (1);
	philosophers = NULL;
	parameters = NULL;
	if (!initial_setup(&philosophers, &parameters, argv))
		return (1);
	parameters->philosophers = philosophers;
	philosophers->parameters = parameters;
	if (!init_parameters(philosophers, parameters))
		return (1);
	if (launch_threads(philosophers, parameters, &monitor_id))
	{
		pthread_join(monitor_id, NULL);
		if (parameters->nb_philo == 1)
			detach_threads(philosophers, parameters);
		join_threads(philosophers, parameters);
	}
	free_structures(philosophers, parameters);
	return (0);
}
