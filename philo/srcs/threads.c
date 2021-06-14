/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:27:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/14 14:39:21 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_t	launch_philosphers(t_philo *philosophers, t_params *parameters)
{
	int			i;
	pthread_t	monitor_id;

	i = 0;
	while (i < parameters->nb_philo && parameters->nb_eat != 0)
	{
		pthread_create(&philosophers[i].thread_id, NULL, \
						&philosopher_loop, &philosophers[i]);
		usleep(50);
		if (i + 2 >= parameters->nb_philo && i % 2 == 0)
			i = 1;
		else
			i += 2;
	}
	pthread_create(&monitor_id, NULL, &philosopher_monitor, philosophers);
	return (monitor_id);
}

void	get_forks(t_philo *philosopher, t_params *parameters)
{
	pthread_mutex_lock(philosopher->left_fork);
	print_fork((*philosopher).id, parameters);
	pthread_mutex_lock(philosopher->right_fork);
	print_fork((*philosopher).id, parameters);
}

void	*philosopher_loop(void *void_philosopher)
{
	t_params	*parameters;
	t_philo		*philosopher;

	philosopher = void_philosopher;
	parameters = philosopher->parameters;
	while (!parameters->end_threads)
	{
		get_forks(philosopher, parameters);
		pthread_mutex_lock(philosopher->eating_lock);
		print_eat((*philosopher).id, parameters);
		philosopher->last_eat = get_time();
		pthread_mutex_unlock(philosopher->eating_lock);
		ft_usleep(parameters->time_eat);
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_lock(philosopher->nb_eat_lock);
		philosopher->nb_eat++;
		pthread_mutex_unlock(philosopher->nb_eat_lock);
		print_sleep((*philosopher).id, parameters);
		ft_usleep(parameters->time_sleep);
		print_think((*philosopher).id, parameters);
	}
	return (NULL);
}
