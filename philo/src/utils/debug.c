/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:41:04 by geibo             #+#    #+#             */
/*   Updated: 2024/07/17 22:16:04 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *str)
{
	printf("Error: %s\n", str);
	exit(1);
}

void	debug(t_table *table)
{
	printf("nb_philos: %d\n", table->nb_philos);
	printf("time_to_die: %d\n", table->time_to_die);
	printf("time_to_eat: %d\n", table->time_to_eat);
	printf("time_to_sleep: %d\n", table->time_to_sleep);
	printf("nb_meals: %d\n", table->nb_meals);
	printf("forks: %p\n", table->forks);
}

void	free_table(t_table *table)
{
	int	i;

	if (table == NULL)
		return ;
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
		free(table->forks);
	}
	free(table);
}

void	free_mutex(t_table *table)
{
	free(table->forks_mutex);
	free(table->last_meal_time_lock);
	free(table->stop_print_lock);
	free(table->die_lock);
	free(table->eating_counter_lock);
}
