/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:53:45 by geibo             #+#    #+#             */
/*   Updated: 2024/11/06 17:31:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo *philo, pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < (size_t)philo->table->num_of_philos)
	{
		pthread_create(&threads[i], NULL, philo_routine, (void *)&philo[i]);
		i++;
	}
}

void	manage_threads(t_philo *philo)
{
	pthread_t	*threads;
	pthread_t	monitor_threads;
	size_t		i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * (philo->table->num_of_philos + 1));
	if (!threads)
	{
		printf("Error: malloc failed\n");
		pthread_exit(NULL);
	}
	philo->table->threads = threads;
	pthread_create(&monitor_threads, NULL, monitor_thread, philo);
	create_threads(philo, threads);
	pthread_join(monitor_threads, NULL);
	while (i < (size_t)philo->table->num_of_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
