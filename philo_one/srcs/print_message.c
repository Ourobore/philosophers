/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:32:50 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/10 11:59:27 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	print_fork(t_philo philosopher, t_params parameters)
{
	int				id;
	unsigned long	timestamp;

	pthread_mutex_lock(philosopher.message);
	//if (!philosopher.end_thread)
	//{
		id = philosopher.id;
		timestamp = get_timestamp(parameters.start_time);
		printf("[%lu] Philosopher [%d] has taken a fork\n", timestamp, id);
	//}
	pthread_mutex_unlock(philosopher.message);
}

void	print_eat(t_philo philosopher, t_params parameters)
{
	int				id;
	unsigned long	timestamp;

	pthread_mutex_lock(philosopher.message);
	//if (!philosopher.end_thread)
	//{
		id = philosopher.id;
		timestamp = get_timestamp(parameters.start_time);
		printf("[%lu] Philosopher [%d] is eating\n", timestamp, id);
	//}
	pthread_mutex_unlock(philosopher.message);
}

void	print_sleep(t_philo philosopher, t_params parameters)
{
	int				id;
	unsigned long	timestamp;

	pthread_mutex_lock(philosopher.message);
	//if (!philosopher.end_thread)
	//{
		id = philosopher.id;
		timestamp = get_timestamp(parameters.start_time);
		printf("[%lu] Philosopher [%d] is sleeping\n", timestamp, id);
	//}
	pthread_mutex_unlock(philosopher.message);
}

void	print_think(t_philo philosopher, t_params parameters)
{
	int				id;
	unsigned long	timestamp;

	pthread_mutex_lock(philosopher.message);
	//if (!philosopher.end_thread)
	//{
		id = philosopher.id;
		timestamp = get_timestamp(parameters.start_time);
		printf("[%lu] Philosopher [%d] is thinking\n", timestamp, id);
	//}
	pthread_mutex_unlock(philosopher.message);
}

void	print_die(t_philo philosopher, t_params parameters)
{
	int				id;
	unsigned long	timestamp;

	pthread_mutex_lock(philosopher.message);
	id = philosopher.id;
	timestamp = get_timestamp(parameters.start_time);
	printf("[%lu] Philosopher [%d] died\n", timestamp, id);
	//pthread_mutex_unlock(philosopher.message);
}
