/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:53:45 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 13:58:40 by geibo            ###   ########.fr       */
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
	size_t		i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * (philo->table->num_of_philos + 1));
	if (!threads)
	{
		printf("Error: malloc failed\n");
		return ;
	}
	philo->table->threads = threads;
	gettimeofday(&philo->table->start_time, NULL);
	create_threads(philo, threads);
	monitor_thread(philo);
	while (i < (size_t)philo->table->num_of_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
