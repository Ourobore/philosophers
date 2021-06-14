/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:32:50 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/14 16:30:17 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_fork(int philo_id, t_params *parameters)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&parameters->message);
	pthread_mutex_lock(&parameters->end);
	if (!parameters->end_threads)
	{
		timestamp = get_timestamp(parameters->start_time);
		printf("[%lu] Philosopher [%d] has taken a fork\n", timestamp, philo_id);
	}
	pthread_mutex_unlock(&parameters->end);
	pthread_mutex_unlock(&parameters->message);
}

void	print_eat(int philo_id, t_params *parameters)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&parameters->message);
	pthread_mutex_lock(&parameters->end);
	if (!parameters->end_threads)
	{
		timestamp = get_timestamp(parameters->start_time);
		printf("[%lu] Philosopher [%d] is eating\n", timestamp, philo_id);
	}
	pthread_mutex_unlock(&parameters->end);
	pthread_mutex_unlock(&parameters->message);
}

void	print_sleep(int philo_id, t_params *parameters)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&parameters->message);
	pthread_mutex_lock(&parameters->end);
	if (!parameters->end_threads)
	{
		timestamp = get_timestamp(parameters->start_time);
		printf("[%lu] Philosopher [%d] is sleeping\n", timestamp, philo_id);
	}
	pthread_mutex_unlock(&parameters->end);
	pthread_mutex_unlock(&parameters->message);
}

void	print_think(int philo_id, t_params *parameters)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&parameters->message);
	pthread_mutex_lock(&parameters->end);
	if (!parameters->end_threads)
	{
		timestamp = get_timestamp(parameters->start_time);
		printf("[%lu] Philosopher [%d] is thinking\n", timestamp, philo_id);
	}
	pthread_mutex_unlock(&parameters->end);
	pthread_mutex_unlock(&parameters->message);
}

void	print_die(int philo_id, t_params *parameters)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&parameters->message);
	timestamp = get_timestamp(parameters->start_time);
	printf("[%lu] Philosopher [%d] died\n", timestamp, philo_id);
	pthread_mutex_lock(&parameters->end);
	parameters->end_threads = 1;
	pthread_mutex_unlock(&parameters->end);
	pthread_mutex_unlock(&parameters->message);
}
