/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:54:07 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 13:54:14 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(t_table *table)
{
	t_philo	*philos;
	size_t	i;

	philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!philos)
	{
		printf("Error: malloc failed\n");
		free(table);
		exit(-1);
	}
	i = 0;
	while (i < (size_t)table->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = get_time();
		philos[i].table = table;
		i++;
	}
	return (philos);
}
