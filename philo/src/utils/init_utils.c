/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 00:11:48 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 09:19:23 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// init_utils.c
void	init_mutexes(t_philo *philos, pthread_mutex_t *forks,
		pthread_mutex_t *print_mutex)
{
	size_t	i;

	i = 0;
	pthread_mutex_init(print_mutex, NULL);
	while (i < (size_t)philos[0].table->num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	assign_forks(t_philo *philos, pthread_mutex_t *forks,
		pthread_mutex_t *print_mutex)
{
	size_t	i;

	i = 0;
	while (i < (size_t)philos->table->num_of_philos)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % philos->table->num_of_philos];
		philos[i].table->print_mutex = print_mutex;
		philos[i].forks = forks;
		i++;
	}
}

void	init_table_values(t_table *table, int argc, char **argv)
{
	table->num_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->num_of_meals = ft_atoi(argv[5]);
	table->start_time = (struct timeval){0};
	if (table->time_to_die <= 60 || table->time_to_eat <= 60
		|| table->time_to_sleep <= 60)
	{
		printf("Error: Time values must be at least 60ms\n");
		free(table);
		exit(-1);
	}
}
