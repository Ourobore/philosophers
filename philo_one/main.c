/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/02 16:39:14 by lchapren         ###   ########.fr       */
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
		philosophers[i].last_eat = params.start_time;
		philosophers[i].id = i;
		philosophers[i].params = &params;
		if (pthread_mutex_init(&(params.forks[i]), NULL) != 0)
			print_error("Error: mutex init failed", 5);
		philosophers[i].left_fork = params.forks[i];
		if (i == params.nb_philo - 1)
			philosophers[i].right_fork = params.forks[0];
		//else if (i == 0 && params.nb_philo == 1)
		//	philosophers[i].right_fork = NULL;
		else
			philosophers[i].right_fork = params.forks[i + 1];
		i++;
	}
	return (params);
}
/*
unsigned long int	get_time_difference(unsigned long int old_time)
{
	struct timeval	time;
	unsigned long int	time_difference;

	gettimeofday(&time, NULL);
	time_difference = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - old_time;
	return (time_difference);
}
*/
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

void	*philosopher_loop(void *void_philo)
{
	t_philo *philo;

	philo = void_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork);
		print_fork(get_timestamp(philo->params->start_time), philo->id, *philo->params);
		pthread_mutex_lock(&philo->right_fork);
		print_fork(get_timestamp(philo->params->start_time), philo->id, *philo->params);
		print_eat(get_timestamp(philo->params->start_time), philo->id, *philo->params);
		printf("[%lu] Last eat before:[%d] %lu\n", get_timestamp(philo->params->start_time), philo->id, get_timestamp(philo->last_eat));
		philo->last_eat = get_time();
		printf("[%lu] Last eat after:[%d] %lu\n", get_timestamp(philo->params->start_time), philo->id, get_timestamp(philo->last_eat));
		ft_usleep(philo->params->time_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		print_sleep(get_timestamp(philo->params->start_time), philo->id, *philo->params);
		ft_usleep(philo->params->time_sleep);
		print_think(get_timestamp(philo->params->start_time), philo->id, *philo->params);
		//ft_usleep(100);
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
	
	struct timeval	time;
	gettimeofday(&time, NULL);
	params.start_time = get_time());
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
		pthread_create(&id, NULL, &philosopher_loop, &params.philo[i]);
		ft_usleep(50);
		if (i + 2 >= params.nb_philo && i % 2 == 0)
			i = 1;
		else
			i += 2;
	}
	while (1)
	{
		i = 0;
		while (i < params.nb_philo)
		{	
			gettimeofday(&time, NULL);
			if (get_timestamp(params.philo[i].last_eat) > (unsigned long int)params.time_die)
			{
				print_die(get_timestamp(params.philo->params->start_time), params.philo->id, params);
				exit(1);
			}
			i++;
		}
	}
	params = clean_parameters(params);
}
