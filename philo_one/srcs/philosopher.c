/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:07:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/02 17:38:28 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

t_params	init_parameters(t_philo *philosophers, t_params params)
{
	int	i;

	i = 0;
	params.start_time = get_time();
	while (i < params.nb_philo)
	{
		philosophers[i].last_eat = params.start_time;
		philosophers[i].id = i;
		philosophers[i].params = &params;
		if (pthread_mutex_init(&(params.forks[i]), NULL) != 0)
			print_error("Error: mutex init failed", 5);
		philosophers[i].left_fork = params.forks[i];
		if (i == params.nb_philo - 1)
			philosophers[i].right_fork = params.forks[0];
		else
			philosophers[i].right_fork = params.forks[i + 1];
		i++;
	}
	return (params);
}

void	*philosopher_loop(void *void_philo)
{
	t_philo *philo;

	philo = void_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork);
		print_fork(get_timestamp(philo->params->start_time), philo->id, *philo->params);
		pthread_mutex_lock(&philo->right_fork);
		print_fork(get_timestamp(philo->params->start_time), philo->id, *philo->params);
		print_eat(get_timestamp(philo->params->start_time), philo->id, *philo->params);
		printf("[%lu] Last eat before:[%d] %lu\n", get_timestamp(philo->params->start_time), philo->id, get_timestamp(philo->last_eat));
		philo->last_eat = get_time();
		printf("[%lu] Last eat after:[%d] %lu\n", get_timestamp(philo->params->start_time), philo->id, get_timestamp(philo->last_eat));
		ft_usleep(philo->params->time_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		print_sleep(get_timestamp(philo->params->start_time), philo->id, *philo->params);
		ft_usleep(philo->params->time_sleep);
		print_think(get_timestamp(philo->params->start_time), philo->id, *philo->params);
		//ft_usleep(100);
	}
}

t_params	clean_parameters(t_params params)
{
	int	i;

	i = 0;
	while (i < params.nb_philo)
	{
		pthread_mutex_destroy(&params.forks[i]);
		i++;
	}
	free(params.forks);
	free(params.philo);
	return (params);
}
