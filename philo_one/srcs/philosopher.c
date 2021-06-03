/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:07:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/03 16:29:59 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

t_params	init_parameters(t_philo *philosophers, t_params parameters)
{
	int	i;

	i = 0;
	parameters.start_time = get_time();
	if (pthread_mutex_init(&parameters.message, NULL) != 0)
		print_error("Error: mutex init failed", 5);
	while (i < parameters.nb_philo)
	{
		if (pthread_mutex_init(&parameters.forks[i], NULL) != 0)
			print_error("Error: mutex init failed", 5);
		i++;
	}
	i = 0;
	while (i < parameters.nb_philo)
	{
		philosophers[i].last_eat = parameters.start_time;
		philosophers[i].id = i + 1;
		philosophers[i].parameters = &parameters;
		philosophers[i].left_fork = parameters.forks[i];
		if (i == parameters.nb_philo - 1)
			philosophers[i].right_fork = parameters.forks[0];
		else
			philosophers[i].right_fork = parameters.forks[i + 1];
		i++;
	}
	return (parameters);
}

void	*philosopher_loop(void *void_philosopher)
{
	t_params	parameters;
	t_philo		*philosopher;

	philosopher = void_philosopher;
	parameters = *philosopher->parameters;
	while (1)
	{
		pthread_mutex_lock(&philosopher->left_fork);
		print_fork(get_timestamp(parameters.start_time), philosopher->id, parameters);
		pthread_mutex_lock(&philosopher->right_fork);
		print_fork(get_timestamp(parameters.start_time), philosopher->id, parameters);
		print_eat(get_timestamp(parameters.start_time), philosopher->id, parameters);
		//printf("[%lu] Last eat before:[%d] %lu\n", get_timestamp(parameters.start_time), philosopher->id, get_timestamp(philosopher->last_eat));
		philosopher->last_eat = get_time();
		//printf("[%lu] Last eat after:[%d] %lu\n", get_timestamp(parameters.start_time), philosopher->id, get_timestamp(philosopher->last_eat));
		ft_usleep(parameters.time_eat);
		pthread_mutex_unlock(&philosopher->left_fork);
		pthread_mutex_unlock(&philosopher->right_fork);
		print_sleep(get_timestamp(parameters.start_time), philosopher->id, parameters);
		ft_usleep(parameters.time_sleep);
		print_think(get_timestamp(parameters.start_time), philosopher->id, parameters);
	}
}

t_params	clean_parameters(t_params parameters)
{
	int	i;

	i = 0;
	while (i < parameters.nb_philo)
	{
		pthread_mutex_destroy(&parameters.forks[i]);
		i++;
	}
	free(parameters.forks);
	free(parameters.philosophers);
	return (parameters);
}
