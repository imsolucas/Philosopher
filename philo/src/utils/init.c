/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:16:12 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 12:48:37 by geibo            ###   ########.fr       */
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

void    sitting(t_philo *philos)
{
    pthread_mutex_t  *forks;
    pthread_mutex_t  *print_mutex;  // Change to pointer

    forks = malloc(sizeof(pthread_mutex_t) * philos->table->num_of_philos);
    print_mutex = malloc(sizeof(pthread_mutex_t));  // Allocate on heap
    if (!forks || !print_mutex)
    {
        printf("Error: malloc failed\n");
        free(forks);
        free(print_mutex);
        free(philos[0].table);
        free(philos);
        exit(-1);
    }
    init_mutexes(philos, forks, print_mutex);
    assign_forks(philos, forks, print_mutex);
}

