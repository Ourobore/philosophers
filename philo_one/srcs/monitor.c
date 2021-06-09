/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:08:15 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/09 13:39:22 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	*philosopher_monitor(void *void_philosophers)
{
	int					i;
	int					eating_done;
	unsigned long int	last_eat;
	t_philo				*philosophers;
	t_params			parameters;

	philosophers = void_philosophers;
	parameters = *philosophers->parameters;
	if (parameters.nb_philo == 0)
		return (NULL);
	while (1)
	{
		i = 0;
		eating_done = 1;
		while (i < parameters.nb_philo)
		{	
			last_eat = get_timestamp(parameters.philosophers[i].last_eat);
			if (last_eat > (unsigned long int)parameters.time_die)
			{
				print_die(get_timestamp(parameters.start_time), philosophers[i]);
				//philosophers[i].end_thread = 1;
				for (int j=0; j< parameters.nb_philo; j++)
					philosophers[j].end_thread = 1;
				ft_usleep(parameters.time_die);
				return (NULL);
			}
			if (parameters.nb_eat != -1 && philosophers->nb_eat < parameters.nb_eat)
				eating_done = 0;
			i++;
		}
		if (parameters.nb_eat != -1 && eating_done)
		{
			for (int j=0; j< parameters.nb_philo; j++)
				philosophers[j].end_thread = 1;
			//pthread_mutex_lock(&parameters.message);
			ft_usleep(parameters.time_die);
			printf("Each philosphers ate at least %d times. End of simulation\n", parameters.nb_eat);
			return (NULL);
		}
		usleep(1000);
	}
}
