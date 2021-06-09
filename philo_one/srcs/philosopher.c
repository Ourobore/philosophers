/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:07:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/09 14:02:58 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

t_params	init_parameters(t_philo *philosophers, t_params parameters)
{
	int	i;

	i = 0;
	parameters.start_time = get_time();
	//parameters.end_threads = 0;
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
		philosophers[i].id = i + 1;
		philosophers[i].parameters = &parameters;
		philosophers[i].message = &parameters.message;
		philosophers[i].last_eat = parameters.start_time;
		philosophers[i].end_thread = 0;
		philosophers[i].nb_eat = 0;
		philosophers[i].left_fork = parameters.forks[i];
		if (i == parameters.nb_philo - 1)
			philosophers[i].right_fork = parameters.forks[0];
		else
			philosophers[i].right_fork = parameters.forks[i + 1];
		i++;
	}
	return (parameters);
}

pthread_t	launch_philosphers(t_philo *philosophers, t_params parameters)
{
	int			i;
	pthread_t	id;

	i = 0;
	while (i < parameters.nb_philo)
	{
		pthread_create(&philosophers[i].thread_id, NULL, &philosopher_loop, &philosophers[i]);
		//pthread_detach(philosophers[i].thread_id);
		usleep(50);
		if (i + 2 >= parameters.nb_philo && i % 2 == 0)
			i = 1;
		else
			i += 2;
	}
	pthread_create(&id, NULL, &philosopher_monitor, philosophers);
	return (id);
}

void	*philosopher_loop(void *void_philosopher)
{
	t_params	parameters;
	t_philo		*philosopher;

	philosopher = void_philosopher;
	parameters = *philosopher->parameters;
	while (!philosopher->end_thread)
	{
		pthread_mutex_lock(&philosopher->left_fork);
		print_fork(get_timestamp(parameters.start_time), *philosopher);
		pthread_mutex_lock(&philosopher->right_fork);
		print_fork(get_timestamp(parameters.start_time), *philosopher);
		print_eat(get_timestamp(parameters.start_time), *philosopher);
		philosopher->last_eat = get_time();
		ft_usleep(parameters.time_eat);
		philosopher->nb_eat++;
		pthread_mutex_unlock(&philosopher->left_fork);
		pthread_mutex_unlock(&philosopher->right_fork);
		print_sleep(get_timestamp(parameters.start_time), *philosopher);
		ft_usleep(parameters.time_sleep);
		print_think(get_timestamp(parameters.start_time), *philosopher);
	}
	return (NULL);
}

void	clean_parameters(t_philo *philosophers, t_params parameters)
{
	int	i;

	i = 0;
	//while (i < parameters.nb_philo)
	//{
	//	philosophers[i].end_thread = 1;
	//	i++;
	//}
	//ft_usleep(parameters.time_die);
	//i = 0;
	while (i < parameters.nb_philo)
	{
		//printf("before join\n");
		pthread_join(philosophers[i].thread_id, NULL);
		pthread_mutex_destroy(&parameters.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&parameters.message);
	free(parameters.forks);
	free(philosophers);
}
