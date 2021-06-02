/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:47:21 by lchapren          #+#    #+#             */
/*   Updated: 2021/06/02 16:47:49 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

unsigned long int	get_time()
{
	struct timeval	time_struct;
	unsigned long int	time;

	gettimeofday(&time_struct, NULL);
	time = (time_struct.tv_sec * 1000) + (time_struct.tv_usec / 1000);
	return (time);
}

unsigned long int	get_timestamp(unsigned long int old_time)
{
	unsigned long int	time;
	unsigned long int	timestamp;

	time = get_time();
	timestamp = time - old_time;
	return (timestamp);
}

void	ft_usleep(unsigned long int	time_ms)
{
	unsigned long int	new_time;

	new_time = get_time() + time_ms;
	while (get_time() < new_time)
		usleep(time_ms);
}