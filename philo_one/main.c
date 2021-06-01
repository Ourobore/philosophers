/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/01 12:00:38 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_params	init_parameters(t_philo *philosophers, t_params params)
{
	int	i;
	struct timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	while (i < params.nb_philo)
	{
		philosophers[i].last_eat = time.tv_sec * 1000;
		philosophers[i].id = i;
		if (pthread_mutex_init(&(params.forks[i]), NULL) != 0)
			print_error("Error: mutex init failed", 5);
		i++;
	}
	return (params);
}

unsigned long int	get_time_difference(unsigned long int old_time)
{
	struct timeval	time;
	unsigned long int	time_difference;

	gettimeofday(&time, NULL);
	time_difference = (time.tv_sec * 1000) - old_time;
	return (time_difference);
}

void	*philosopher_loop(void *void_params)
{
	t_params *params;

	params = void_params;
	while (1)
	{
		//pthread_mutex_lock(&params.forks[0]);
		printf("[%lu] Philospher [%d] has taken a fork\n", get_time_difference(params->start_time), params->philo->id + 1);
		usleep(1000000);
		//pthread_mutex_unlock(&params.forks[0]);
	}
}

t_params	clean_parameters(t_params params)
{
	int	i;

	i = 0;
	while (i < params.nb_philo)
	{
		pthread_mutex_destroy(&params.forks[i]);
		i++;
	}
	free(params.forks);
	free(params.philo);
	return (params);
}

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
	
    params.philo = NULL;
    params.philo = malloc(sizeof(t_philo) * params.nb_philo);
    if (!params.philo)
        print_error("Error: malloc failed", 1);
	memset(params.philo, 0, params.nb_philo);
	
	params.forks = NULL;
	params.forks = malloc(sizeof(pthread_mutex_t) * params.nb_philo);
	if (!params.forks)
        print_error("Error: malloc failed", 1);
	memset(params.forks, 0, params.nb_philo);

	params = init_parameters(params.philo, params);

	int	i = 0;
	pthread_t id;
	while (i < params.nb_philo)
	{
		pthread_create(&id, NULL, &philosopher_loop, &params);
		i++;
	}
	while (1)
	{}
	params = clean_parameters(params);
}
