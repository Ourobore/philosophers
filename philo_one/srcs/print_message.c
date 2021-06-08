/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:32:50 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/08 11:41:01 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	print_eat(unsigned long int timestamp, t_philo philosopher)
{
	pthread_mutex_lock(philosopher.message);
	printf("[%lu] Philosopher [%d] is eating\n", timestamp, philosopher.id);
	pthread_mutex_unlock(philosopher.message);
}

void	print_sleep(unsigned long int timestamp, t_philo philosopher)
{
	pthread_mutex_lock(philosopher.message);
	printf("[%lu] Philosopher [%d] is sleeping\n", timestamp, philosopher.id);
	pthread_mutex_unlock(philosopher.message);
}

void	print_think(unsigned long int timestamp, t_philo philosopher)
{
	pthread_mutex_lock(philosopher.message);
	printf("[%lu] Philosopher [%d] is thinking\n", timestamp, philosopher.id);
	pthread_mutex_unlock(philosopher.message);
}

void	print_die(unsigned long int timestamp, t_philo philosopher)
{
	pthread_mutex_lock(philosopher.message);
	printf("[%lu] Philosopher [%d] died\n", timestamp, philosopher.id);
	//pthread_mutex_unlock(philosopher.message);
}

void	print_fork(unsigned long int timestamp, t_philo philosopher)
{
	pthread_mutex_lock(philosopher.message);
	printf("[%lu] Philosopher [%d] has taken a fork\n", timestamp, philosopher.id);
	pthread_mutex_unlock(philosopher.message);
}
