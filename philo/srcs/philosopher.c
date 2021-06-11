/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:07:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/11 10:34:04 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	mutex_initialization(t_params *parameters)
{
	int	i;

	if (pthread_mutex_init(&parameters->message, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		return (0);
	}
	parameters->forks = init_forks(parameters);
	if (!parameters->forks)
	{
		printf("Error: malloc failed\n");
		return (0);
	}
	i = 0;
	while (i < parameters->nb_philo)
	{
		if (pthread_mutex_init(&parameters->forks[i], NULL) != 0)
		{
			printf("Error: mutex init failed\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_parameters(t_philo *philosophers, t_params *parameters)
{
	int	i;

	if (!mutex_initialization(parameters))
	{
		free_structures(philosophers, parameters);
		return (0);
	}
	i = 0;
	parameters->start_time = get_time();
	while (i < parameters->nb_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].nb_eat = 0;
		philosophers[i].parameters = parameters;
		philosophers[i].last_eat = parameters->start_time;
		philosophers[i].left_fork = &parameters->forks[i];
		if (i == parameters->nb_philo - 1)
			philosophers[i].right_fork = &parameters->forks[0];
		else
			philosophers[i].right_fork = &parameters->forks[i + 1];
		i++;
	}
	return (1);
}

pthread_t	launch_philosphers(t_philo *philosophers, t_params *parameters)
{
	int			i;
	pthread_t	id;

	i = 0;
	while (i < parameters->nb_philo && parameters->nb_eat != 0)
	{
		pthread_create(&id, NULL, &philosopher_loop, &philosophers[i]);
		pthread_detach(id);
		usleep(50);
		if (i + 2 >= parameters->nb_philo && i % 2 == 0)
			i = 1;
		else
			i += 2;
	}
	pthread_create(&id, NULL, &philosopher_monitor, philosophers);
	return (id);
}

void	*philosopher_loop(void *void_philosopher)
{
	t_params	*parameters;
	t_philo		*philosopher;

	philosopher = void_philosopher;
	parameters = philosopher->parameters;
	while (1)
	{
		pthread_mutex_lock(philosopher->left_fork);
		print_fork((*philosopher).id, parameters);
		pthread_mutex_lock(philosopher->right_fork);
		print_fork((*philosopher).id, parameters);
		print_eat((*philosopher).id, parameters);
		philosopher->last_eat = get_time();
		ft_usleep(parameters->time_eat);
		philosopher->nb_eat++;
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		print_sleep((*philosopher).id, parameters);
		ft_usleep(parameters->time_sleep);
		print_think((*philosopher).id, parameters);
	}
}
