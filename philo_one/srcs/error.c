/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:18:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/10 17:44:33 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

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
				pthread_mutex_destroy(&parameters->forks[i]);
				i++;
			}
			free(parameters->forks);
		}
		free(parameters);
	}
}
