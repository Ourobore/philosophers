/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lil_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:26:37 by user42            #+#    #+#             */
/*   Updated: 2021/06/11 09:52:39 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	lil_atoi(const char *str)
{
	unsigned long int	i;
	unsigned long int	nb;

	i = 0;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0' || nb > INT_MAX)
		return (-1);
	return (nb);
}
