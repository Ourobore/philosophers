/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:32:50 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/07 16:42:12 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	print_eat(unsigned long int timestamp, int philo_id, t_params params)
{
	pthread_mutex_lock(&params.message);
	printf("[%lu] Philosopher [%d] is eating\n", timestamp, philo_id);
	pthread_mutex_unlock(&params.message);
}

void	print_sleep(unsigned long int timestamp, int philo_id, t_params params)
{
	pthread_mutex_lock(&params.message);
	printf("[%lu] Philosopher [%d] is sleeping\n", timestamp, philo_id);
	pthread_mutex_unlock(&params.message);
}

void	print_think(unsigned long int timestamp, int philo_id, t_params params)
{
	pthread_mutex_lock(&params.message);
	printf("[%lu] Philosopher [%d] is thinking\n", timestamp, philo_id);
	pthread_mutex_unlock(&params.message);
}

void	print_die(unsigned long int timestamp, int philo_id, t_params params)
{
	pthread_mutex_lock(&params.message);
	printf("[%lu] Philosopher [%d] died\n", timestamp, philo_id);
	//ft_usleep(params.time_die);
	//pthread_mutex_unlock(&params.message);
}

void	print_fork(unsigned long int timestamp, int philo_id, t_params params)
{
	pthread_mutex_lock(&params.message);
	printf("[%lu] Philosopher [%d] has taken a fork\n", timestamp, philo_id);
	pthread_mutex_unlock(&params.message);
}
