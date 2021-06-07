/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:08:15 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/07 12:20:34 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	philosphers_monitor(void *void_philosophers)
{
	int					i;
	unsigned long int	last_eat;
	t_philo				*philosophers;
	t_params			parameters;

	philosophers = void_philosophers;
	parameters = *philosophers->parameters;
	while (1)
	{
		i = 0;
		while (i < parameters.nb_philo)
		{	
			last_eat = get_timestamp(parameters.philosophers[i].last_eat);
			if (last_eat > (unsigned long int)parameters.time_die + 10)
			{
				print_die(get_timestamp(parameters.start_time), philosophers[i].id, parameters);
				exit(1);
			}
			ft_usleep(50);
			i++;
		}
	}
	parameters = clean_parameters(parameters);
}
