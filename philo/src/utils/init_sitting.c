/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sitting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:53:21 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 13:56:20 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutexes(t_philo *philos, pthread_mutex_t *forks,
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

void	sitting(t_philo *philos)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	size_t			i;

	forks = malloc(sizeof(pthread_mutex_t) * philos->table->num_of_philos);
	print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!forks || !print_mutex)
	{
		printf("Error: malloc failed\n");
		free(forks);
		free(print_mutex);
		free(philos[0].table);
		free(philos);
		exit(-1);
	}
	init_mutexes(philos, forks, print_mutex);
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
