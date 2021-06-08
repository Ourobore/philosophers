/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 10:31:06 by user42            #+#    #+#             */
/*   Updated: 2021/06/08 14:46:20 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	monitor(t_philo *philosophers, t_params parameters)
{
	int					i;
	int					eating_done;
	unsigned long int	last_eat;
	
	if (parameters.nb_philo == 0)
		return ;
	while (1)
	{
		i = 0;
		eating_done = 1;
		while (i < parameters.nb_philo)
		{	
			last_eat = get_timestamp(parameters.philosophers[i].last_eat);
			if (last_eat > (unsigned long int)parameters.time_die)
			{
				print_die(get_timestamp(parameters.start_time), philosophers[i]);
				ft_usleep(parameters.time_die);
				return ;
			}
			if (parameters.nb_eat != -1 && philosophers->nb_eat < parameters.nb_eat)
				eating_done = 0;
			i++;
		}
		if (parameters.nb_eat != -1 && eating_done)
		{
			printf("Each philosphers ate at least %d times. End of simulation\n", parameters.nb_eat);
			return ;
		}
		usleep(1000);
	}
}

int	main(int argc, char *argv[])
{
	pthread_t	monitor_id;
	t_params	parameters;
	t_philo		*philosophers;

	if (argc != 5 && argc != 6)
		print_error("Error: wrong number of parameters", 2);
	parameters = get_parameters(argv);
	philosophers = init_philo(parameters);
	parameters.philosophers = philosophers;
	parameters.forks = init_forks(parameters);
	parameters = init_parameters(philosophers, parameters);
	if (!(parameters.nb_philo == 0 || parameters.nb_eat == 0))
		monitor_id = launch_philosphers(philosophers, parameters);
	monitor(philosophers, parameters);
	//pthread_join(monitor_id, NULL);
	printf("out\n");
	parameters = clean_parameters(parameters);
}
