/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:48:02 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/14 14:59:42 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_philo_mutexes(t_params *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->nb_philo)
	{
		pthread_mutex_destroy(&parameters->forks[i]);
		pthread_mutex_destroy(&parameters->mutexes_eating[i]);
		pthread_mutex_destroy(&parameters->mutexes_nb_eat[i]);
		i++;
	}
}

void	free_structures(t_philo *philosophers, t_params *parameters)
{
	if (parameters)
	{
		if (parameters->forks)
		{
			destroy_philo_mutexes(parameters);
			free(parameters->forks);
		}
		pthread_mutex_destroy(&parameters->message);
		pthread_mutex_destroy(&parameters->end);
		if (parameters->mutexes_eating)
			free(parameters->mutexes_eating);
		if (parameters->mutexes_nb_eat)
			free(parameters->mutexes_nb_eat);
		free(parameters);
	}
	if (philosophers)
		free(philosophers);
}
