/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 13:16:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/10 16:36:38 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

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

t_philo	*init_philo(t_params *parameters)
{
	t_philo	*philosophers;

	philosophers = NULL;
	philosophers = malloc(sizeof(t_philo) * parameters->nb_philo);
	if (!philosophers)
	{
		free(parameters);
		return (NULL);
	}
	memset(philosophers, 0, parameters->nb_philo);
	return (philosophers);
}

pthread_mutex_t	*init_forks(t_params *parameters)
{
	pthread_mutex_t	*forks;

	forks = NULL;
	forks = malloc(sizeof(pthread_mutex_t) * parameters->nb_philo);
	if (!forks)
	{
		printf("Error: malloc failed\n");
		return (NULL);
	}
	memset(forks, 0, parameters->nb_philo);
	return (forks);
}
