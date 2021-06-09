/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:32:50 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/09 15:30:49 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	print_eat(unsigned long int timestamp, t_philo philosopher)
{
	int	id;

	pthread_mutex_lock(philosopher.message);
	if (!philosopher.end_thread)
	{
		id = philosopher.id;
		printf("[%lu] Philosopher [%d] is eating\n", timestamp, id);
	}
	pthread_mutex_unlock(philosopher.message);
}

void	print_sleep(unsigned long int timestamp, t_philo philosopher)
{
	int	id;

	pthread_mutex_lock(philosopher.message);
	if (!philosopher.end_thread)
	{
		id = philosopher.id;
		printf("[%lu] Philosopher [%d] is sleeping\n", timestamp, id);
	}
	pthread_mutex_unlock(philosopher.message);
}

void	print_think(unsigned long int timestamp, t_philo philosopher)
{
	int	id;

	pthread_mutex_lock(philosopher.message);
	if (!philosopher.end_thread)
	{
		id = philosopher.id;
		printf("[%lu] Philosopher [%d] is thinking\n", timestamp, id);
	}
	pthread_mutex_unlock(philosopher.message);
}

void	print_die(unsigned long int timestamp, t_philo philosopher)
{
	int	id;

	pthread_mutex_lock(philosopher.message);
	if (!philosopher.end_thread)
	{
		id = philosopher.id;
		printf("[%lu] Philosopher [%d] died\n", timestamp, id);
	}
	pthread_mutex_unlock(philosopher.message);
}

void	print_fork(unsigned long int timestamp, t_philo philosopher)
{
	int	id;

	pthread_mutex_lock(philosopher.message);
	if (!philosopher.end_thread)
	{
		id = philosopher.id;
		printf("[%lu] Philosopher [%d] has taken a fork\n", timestamp, id);
	}
	pthread_mutex_unlock(philosopher.message);
}
