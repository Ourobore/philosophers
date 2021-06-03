/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/03 14:12:43 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char *argv[])
{
	t_params	params;

	if (argc != 5 && argc != 6)
    	print_error("Error: wrong number of parameters", 2);
	params = get_parameters(argv);
	printf("nb_philo: %d\n", params.nb_philo);
	printf("time_die: %d\n", params.time_die);
	printf("time_eat: %d\n", params.time_eat);
	printf("time_sleep: %d\n", params.time_sleep);
	if (argc == 6)
		printf("nb_eat: %d\n", params.nb_eat);

	params.philo = NULL;
	params.philo = malloc(sizeof(t_philo) * params.nb_philo);
	if (!params.philo)
	print_error("Error: malloc failed", 1);
	memset(params.philo, 0, params.nb_philo);

	params.forks = NULL;
	params.forks = malloc(sizeof(pthread_mutex_t) * params.nb_philo);
	if (!params.forks)
		print_error("Error: malloc failed", 1);
	memset(params.forks, 0, params.nb_philo);

	params = init_parameters(params.philo, params);

	int	i = 0;
	pthread_t id;
	while (i < params.nb_philo)
	{
		pthread_create(&id, NULL, &philosopher_loop, &params.philo[i]);
		ft_usleep(50);
		if (i + 2 >= params.nb_philo && i % 2 == 0)
			i = 1;
		else
			i += 2;
	}
	while (1)
	{
		i = 0;
		while (i < params.nb_philo)
		{	
			if (get_timestamp(params.philo[i].last_eat) > (unsigned long int)params.time_die)
			{
				print_die(get_timestamp(params.philo->params->start_time), params.philo->id, params);
				exit(1);
			}
			i++;
		}
	}
	params = clean_parameters(params);
}
