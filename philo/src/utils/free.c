/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:19:45 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 00:49:08 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up_tables(t_philo *philos, t_table *table)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(table->print_mutex);
	while (i < (size_t)philos->table->num_of_philos)
	{
		pthread_mutex_destroy(&philos[i].forks[i]);
		i++;
	}
	free(philos->table->someone_died);
	free(philos->table->threads);
	free(philos->forks);
	free(philos);
	free(table);
}