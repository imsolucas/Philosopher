/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:04:48 by geibo             #+#    #+#             */
/*   Updated: 2024/07/17 22:38:41 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_up_tables(t_table *table)
{
	if (!initialize_mutex(&table->forks_mutex, table->nb_philos)
		|| !initialize_mutex(&table->last_meal_time_lock, table->nb_philos)
		|| !initialize_mutex(&table->stop_print_lock, 1)
		|| !initialize_mutex(&table->die_lock, 1)
		|| !initialize_mutex(&table->eating_counter_lock, 1))
	{
		free_mutex(table);
		exit(1);
	}
	table->stop = false;
}

void	set_up_forks(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philos)
	{
		table->forks[i] = 1;
		i++;
	}
}

static	pthread_mutex_t	*create_mutex(size_t size)
{
	pthread_mutex_t	*mutex;
	size_t			i;

	mutex = malloc(sizeof(pthread_mutex_t) * size);
	if (!mutex)
	{
		printf("Error: malloc failed\n");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		if (!pthread_mutex_init(&mutex[i], NULL))
		{
			printf("Error: mutex init failed\n");
			return (NULL);
		}
		i++;
	}
	return (mutex);
}

bool	initialize_mutex(pthread_mutex_t **mutex, t_table *table)
{
	*mutex = create_mutex(table->nb_philos);
	// printf("Hello from initialize_mutex\n");
	return (*mutex != NULL);
}
