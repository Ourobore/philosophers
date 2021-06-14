/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 13:16:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/14 13:25:18 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

pthread_mutex_t	*init_forks(t_params *parameters)
{
	pthread_mutex_t	*forks;

	forks = NULL;
	forks = malloc(sizeof(pthread_mutex_t) * parameters->nb_philo);
	if (!forks)
		return (NULL);
	memset(forks, 0, parameters->nb_philo);
	return (forks);
}

void	free_structures(t_philo *philosophers, t_params *parameters)
{
	int	i;

	if (philosophers)
		free(philosophers);
	if (parameters)
	{
		i = 0;
		pthread_mutex_destroy(&parameters->message);
		if (parameters->forks)
		{
			while (i < parameters->nb_philo)
			{
				pthread_join(philosophers[i].thread_id, NULL);
				pthread_mutex_destroy(&parameters->forks[i]);
				pthread_mutex_destroy(&parameters->mutexes_eating[i]);
				pthread_mutex_destroy(&parameters->mutexes_nb_eat[i]);
				i++;
			}
			free(parameters->forks);
		}
		free(parameters->mutexes_eating);
		free(parameters->mutexes_nb_eat);
		free(parameters);
	}
}
