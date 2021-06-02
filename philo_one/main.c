/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/02 12:11:54 by lchapren         ###   ########.fr       */
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

unsigned long int	get_time_difference(unsigned long int old_time)
{
	struct timeval	time;
	unsigned long int	time_difference;

	gettimeofday(&time, NULL);
	time_difference = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - old_time;
	return (time_difference);
}

void	ft_usleep(int	time_ms)
{
	int	i;
	int	nb_usleep;

	i = 0;
	nb_usleep = 1000;
	while (i < nb_usleep)
	{
		usleep(time_ms / nb_usleep);
		i++;
	}
}

void	*philosopher_loop(void *void_philo)
{
	t_philo *philo;

	philo = void_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->params->message);
		printf("[%lu] Philospher [%d] has taken a fork\n", get_time_difference(philo->params->start_time), philo->id + 1);
		pthread_mutex_unlock(&philo->params->message);
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->params->message);
		printf("[%lu] Philospher [%d] has taken a fork\n", get_time_difference(philo->params->start_time), philo->id + 1);
		printf("[%lu] Philospher [%d] is eating\n", get_time_difference(philo->params->start_time), philo->id + 1);
		pthread_mutex_unlock(&philo->params->message);
		ft_usleep(philo->params->time_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_lock(&philo->params->message);
		printf("[%lu] Philospher [%d] is sleeping\n", get_time_difference(philo->params->start_time), philo->id + 1);
		pthread_mutex_unlock(&philo->params->message);
		ft_usleep(philo->params->time_sleep);
		pthread_mutex_lock(&philo->params->message);
		printf("[%lu] Philospher [%d] is thinking\n", get_time_difference(philo->params->start_time), philo->id + 1);
		pthread_mutex_unlock(&philo->params->message);
		//printf("Message unlock\n");
		//if 
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
	params.start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
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
		i++;
	}
	while (1)
	{}
	params = clean_parameters(params);
}
