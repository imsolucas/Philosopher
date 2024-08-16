/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:04:48 by geibo             #+#    #+#             */
/*   Updated: 2024/08/16 23:59:43 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_up_tables(t_table *table)
{
	table->forks_mutex = create_mutex(table->nb_philos);
	table->last_meal_time_lock = create_mutex(table->nb_philos);
	table->stop_print_lock = create_mutex(1);
	table->die_lock = create_mutex(1);
	table->eating_counter_lock = create_mutex(table->nb_philos);
	table->stop_printing = false;
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
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}

