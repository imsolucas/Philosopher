/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:19:45 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 02:46:54 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up_tables(t_philo *philos, t_table *table)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(table->print_mutex);
	pthread_mutex_destroy(table->last_meal_mutex);
	pthread_mutex_destroy(table->meals_eaten_mutex);
	while (i < (size_t)philos->table->num_of_philos)
	{
		pthread_mutex_destroy(&philos[i].forks[i]);
		i++;
	}
	free(philos->table->someone_died);
	free(philos->table->threads);
	free(philos->table->print_mutex);
	free(philos->table->last_meal_mutex);
	free(philos->table->meals_eaten_mutex);
	free(philos->forks);
	free(philos);
	free(table);
}
