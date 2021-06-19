/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:07:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/19 09:55:13 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	mutex_init(t_params *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->nb_philo)
	{
		if (pthread_mutex_init(&parameters->forks[i], NULL) != 0)
		{
			printf("Error: mutex init failed\n");
			return (0);
		}
		if (pthread_mutex_init(&parameters->mutexes_eating[i], NULL) != 0)
		{
			printf("Error: mutex init failed\n");
			return (0);
		}
		if (pthread_mutex_init(&parameters->mutexes_nb_eat[i], NULL) != 0)
		{
			printf("Error: mutex init failed\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	mutex_creation(t_params *parameters)
{
	if (pthread_mutex_init(&parameters->message, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		return (0);
	}
	if (pthread_mutex_init(&parameters->end, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		return (0);
	}
	if (!malloc_mutexes(&parameters))
		return (0);
	if (!mutex_init(parameters))
		return (0);
	return (1);
}

void	give_forks(t_philo *philosophers, t_params *parameters, int i)
{
	philosophers[i].left_fork = &parameters->forks[i];
	if (i == parameters->nb_philo - 1)
		philosophers[i].right_fork = &parameters->forks[0];
	else
		philosophers[i].right_fork = &parameters->forks[i + 1];
}

int	init_parameters(t_philo *philosophers, t_params *parameters)
{
	int	i;

	if (!mutex_creation(parameters))
	{
		free_structures(philosophers, parameters);
		return (0);
	}
	i = 0;
	parameters->start_time = get_time();
	parameters->end_threads = 0;
	while (i < parameters->nb_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].nb_eat = 0;
		philosophers[i].parameters = parameters;
		philosophers[i].last_eat = parameters->start_time;
		philosophers[i].eating_lock = &parameters->mutexes_eating[i];
		philosophers[i].nb_eat_lock = &parameters->mutexes_nb_eat[i];
		give_forks(philosophers, parameters, i);
		i++;
	}
	return (1);
}

void	detach_threads(t_philo *philosophers, t_params *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->nb_philo)
	{
		pthread_detach(philosophers[i].thread_id);
		i++;
	}
}
