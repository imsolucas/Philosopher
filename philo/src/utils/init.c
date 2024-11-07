/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:16:12 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 13:54:56 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_zero(t_table *table)
{
	table->num_of_philos = 0;
	table->num_of_meals = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->print_mutex = NULL;
	table->someone_died = NULL;
}

t_table	*alloc_table(void)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
	{
		printf("Error: malloc failed\n");
		exit(-1);
	}
	return (table);
}

t_table	*set_up_table(int argc, char **argv)
{
	t_table	*table;

	table = alloc_table();
	set_zero(table);
	init_table_values(table, argc, argv);
	table->someone_died = malloc(sizeof(bool));
	if (!table->someone_died)
	{
		printf("Error: malloc failed\n");
		free(table);
		exit(-1);
	}
	*table->someone_died = false;
	return (table);
}
