/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/08 11:43:52 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char *argv[])
{
	pthread_t	monitor_id;
	t_params	parameters;
	t_philo		*philosophers;

	if (argc != 5 && argc != 6)
		print_error("Error: wrong number of parameters", 2);
	parameters = get_parameters(argv);
	philosophers = init_philo(parameters);
	parameters.philosophers = philosophers;
	parameters.forks = init_forks(parameters);
	parameters = init_parameters(philosophers, parameters);
	monitor_id = launch_philosphers(philosophers, parameters);
	pthread_join(monitor_id, NULL);
	parameters = clean_parameters(parameters);
}
