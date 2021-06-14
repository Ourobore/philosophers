/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 13:16:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/14 15:15:02 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_parameters(char *argv[], t_params *parameters)
{
	int			i;
	int			value;

	i = 1;
	while (argv[i])
	{
		value = lil_atoi(argv[i]);
		if (value == -1)
			return (0);
		if (i == 1)
			parameters->nb_philo = value;
		else if (i == 2)
			parameters->time_die = value;
		else if (i == 3)
			parameters->time_eat = value;
		else if (i == 4)
			parameters->time_sleep = value;
		else if (i == 5)
			parameters->nb_eat = value;
		i++;
	}
	if (i == 5)
		parameters->nb_eat = -1;
	return (1);
}

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
	if ((*parameters)->nb_philo == 0)
	{
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

int	malloc_mutexes(t_params **parameters)
{
	(*parameters)->forks = NULL;
	(*parameters)->mutexes_eating = NULL;
	(*parameters)->mutexes_nb_eat = NULL;
	(*parameters)->forks = malloc(sizeof(pthread_mutex_t) * \
								(*parameters)->nb_philo);
	(*parameters)->mutexes_eating = malloc(sizeof(pthread_mutex_t) * \
										(*parameters)->nb_philo);
	(*parameters)->mutexes_nb_eat = malloc(sizeof(pthread_mutex_t) * \
										(*parameters)->nb_philo);
	if (!(*parameters)->forks || !(*parameters)->mutexes_eating || \
		!(*parameters)->mutexes_nb_eat)
	{
		printf("Error: malloc failed\n");
		return (0);
	}
	memset((*parameters)->forks, 0, (*parameters)->nb_philo);
	memset((*parameters)->mutexes_eating, 0, (*parameters)->nb_philo);
	memset((*parameters)->mutexes_nb_eat, 0, (*parameters)->nb_philo);
	return (1);
}
