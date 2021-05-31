/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/05/31 14:23:16 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int main(int argc, char *argv[])
{
    t_params	params;

    if (argc != 5 && argc != 6)
        print_error("Error: wrong number of parameters", 2);
    params = get_parameters(argv);
    printf("nb_philo: %d\n", params.nb_philo);
    printf("time_die: %d\n", params.time_die);
    printf("time_eat: %d\n", params.time_eat);
    printf("time_sleep: %d\n", params.time_sleep);
    if (argc == 6)
        printf("nb_eat: %d\n", params.nb_eat);
    
    t_philo *philosopher_table;

    philosopher_table = NULL;
    philosopher_table = malloc(sizeof(t_philo) * params.nb_philo);
    if (!philosopher_table)
        print_error("Error: malloc failed", 1);
	philosopher_table = init_philosophers(philosopher_table, params);
	
	phtread_mutex_t	fork_lock;

	if (phtread_mutex_init(&fork_lock, NULL))
		print_error("Error: mutex init failed", 4);
}

t_philo	*init_philosophers(t_philo *philosopher_table, t_params params)
{
	int	i;
	struct timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	while (i < params.nb_philo)
	{
		philosopher_table[i].last_eat = time.tv_sec * 1000;
		i++;
	}
}


int	philosopher_loop(t_philo philosopher, t_params params, phtread_mutex_t *fork_lock)
{
	while (1)
	{
		pthread_mutex_lock(fork_lock);
		pthread_mutex_unlock(fork_lock);
	}
}