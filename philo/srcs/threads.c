/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:27:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/19 09:58:50 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	launch_threads(t_philo *philo, t_params *params, pthread_t *monitor_id)
{
	int			i;

	i = 0;
	while (i < params->nb_philo && params->nb_eat != 0)
	{
		if (pthread_create(&philo[i].thread_id, NULL, \
						&philosopher_loop, &philo[i]) != 0)
		{
			printf("Error: thread_creation failed\n");
			return (0);
		}
		usleep(50);
		if (i + 2 >= params->nb_philo && i % 2 == 0)
			i = 1;
		else
			i += 2;
	}
	if (pthread_create(monitor_id, NULL, \
					&philosopher_monitor, philo) != 0)
	{
		printf("Error: thread_creation failed\n");
		detach_threads(philo, params);
		return (0);
	}
	return (1);
}

void	get_forks(t_philo *philosopher, t_params *parameters)
{
	pthread_mutex_lock(philosopher->left_fork);
	print_fork((*philosopher).id, parameters);
	pthread_mutex_lock(philosopher->right_fork);
	print_fork((*philosopher).id, parameters);
}

int	should_end(t_params *parameters)
{
	pthread_mutex_lock(&parameters->end);
	if (parameters->end_threads == 1)
	{
		pthread_mutex_unlock(&parameters->end);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&parameters->end);
		return (0);
	}
}

void	*philosopher_loop(void *void_philosopher)
{
	t_params	*parameters;
	t_philo		*philosopher;

	philosopher = void_philosopher;
	parameters = philosopher->parameters;
	while (!should_end(parameters))
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
