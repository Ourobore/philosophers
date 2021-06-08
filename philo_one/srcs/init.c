/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 13:16:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/08 14:36:19 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

t_params	get_parameters(char *argv[])
{
	int			i;
	int			value;
	t_params	params;

	i = 1;
	while (argv[i])
	{
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
	if (i == 5)
		params.nb_eat = -1;
	return (params);
}

t_philo	*init_philo(t_params parameters)
{
	t_philo	*philosophers;

	philosophers = NULL;
	philosophers = malloc(sizeof(t_philo) * parameters.nb_philo);
	if (!philosophers)
		print_error("Error: malloc failed", 1);
	memset(philosophers, 0, parameters.nb_philo);
	return (philosophers);
}

pthread_mutex_t	*init_forks(t_params parameters)
{
	pthread_mutex_t	*forks;

	forks = NULL;
	forks = malloc(sizeof(pthread_mutex_t) * parameters.nb_philo);
	if (!forks)
		print_error("Error: malloc failed", 1);
	memset(forks, 0, parameters.nb_philo);
	return (forks);
}
