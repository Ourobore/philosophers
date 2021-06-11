/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:08:15 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/11 10:06:27 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	verify_death(t_philo *philosophers, t_params *parameters, int eating_done)
{
	int				i;
	unsigned long	last_eat;

	i = 0;
	while (i < parameters->nb_philo)
	{	
		last_eat = get_timestamp(philosophers[i].last_eat);
		if (last_eat > (unsigned long int)parameters->time_die)
		{
			print_die(philosophers[i].id, parameters);
			return (-1);
		}
		if (philosophers->nb_eat < parameters->nb_eat)
			eating_done = 0;
		i++;
	}
	return (eating_done);
}

void	*philosopher_monitor(void *void_philosophers)
{
	int			eating_done;
	t_philo		*philosophers;
	t_params	*parameters;

	philosophers = void_philosophers;
	parameters = philosophers->parameters;
	if (parameters->nb_philo == 0)
		return (NULL);
	while (1)
	{
		eating_done = 1;
		eating_done = verify_death(philosophers, parameters, eating_done);
		if (eating_done == -1)
			return (NULL);
		if (parameters->nb_eat != -1 && eating_done == 1)
		{
			pthread_mutex_lock(&parameters->message);
			printf("Each philosphers ate at least %d times. " \
					"End of simulation\n", parameters->nb_eat);
			return (NULL);
		}
		usleep(1000);
	}
}
