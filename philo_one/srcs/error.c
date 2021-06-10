/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:18:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/10 15:01:54 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	*no_error(char *message, void *arg)
{
	if (!arg)
	{
		printf("%s\n", message);
		return (NULL);
	}
	else
		return (arg);
}

void	free_structures(t_philo *philosophers, t_params *parameters)
{
	if (philosophers)
	{
		if (philosophers->left_fork)
			pthread_mutex_destroy(philosophers->left_fork);
		if (philosophers->right_fork)
			pthread_mutex_destroy(philosophers->right_fork);
		if (philosophers->message)
			pthread_mutex_destroy(philosophers->message);
	}
	if (parameters)
	{
		free(parameters);
	}
	free(philosophers);
}
