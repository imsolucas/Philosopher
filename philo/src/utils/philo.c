/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:17:20 by geibo             #+#    #+#             */
/*   Updated: 2024/08/17 01:11:16 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		grab_forks(philo, table);
		handle_eat(philo, table);
		release_forks(philo, table);
		sleeping(philo, table);
		die(philo, table);
		thinking(philo, table);
	}
}

void	create_threads(t_philo **philo, t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_create(&philo[i]->thread, NULL, philo_routine, (void *)philo[i]);
		i++;
	}
}

void	join_threads(t_philo **philo, t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(philo[i]->thread, NULL);
		i++;
	}
}

void	manage_threads(t_philo **philo, t_table *table)
{
	gettimeofday(&table->start_time, NULL);
	table->time = convert_to_ms(table->start_time);
	create_threads(philo, table);
	monitor_threads(philo, table);
	join_threads(philo, table);
}
