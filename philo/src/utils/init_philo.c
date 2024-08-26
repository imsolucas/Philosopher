/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:35:12 by geibo             #+#    #+#             */
/*   Updated: 2024/08/22 01:15:04 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*set_zero(t_table *table)
{
	table->nb_philos = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->nb_meals = -1;
	table->forks = NULL;
	table->philos = NULL;
	table->forks_mutex = NULL;
	table->last_meal_time_lock = NULL;
	table->stop_print_lock = NULL;
	table->log_mutex = NULL;
	table->eating_counter_lock = NULL;
	return (table);
}

t_table	*init_philo(t_table *table, int argc, char **argv)
{
	int	i;

	i = 0;
	table = malloc(sizeof(t_table));
	table = set_zero(table);
	if (!table)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	while (i < argc)
	{
		if (i == 1)
			table->nb_philos = ft_atoi(argv[i]);
		else if (i == 2)
			table->time_to_die = ft_atoi(argv[i]);
		else if (i == 3)
			table->time_to_eat = ft_atoi(argv[i]);
		else if (i == 4)
			table->time_to_sleep = ft_atoi(argv[i]);
		else if (i == 5)
			table->nb_meals = ft_atoi(argv[i]);
		i++;
	}
	return (table);
}

t_philo	**set_up_philos(t_table *table)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo *) * table->nb_philos);
	table->forks = malloc(sizeof(size_t) * table->nb_philos);
	if (!philos && !table->forks)
		error_exit("malloc failed");
	set_up_forks(table);
	while (i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			error_exit("malloc failed");
		philos[i]->id = i;
		philos[i]->table = table;
		philos[i]->total_meals = 0;
		philos[i]->thread = 0;
		assign_forks(philos[i]);
		philos[i]->table = table;
		i++;
	}
	return (philos);
}

static void	assign_forks(t_philo *philo)
{
	philo->forks[0] = philo->id;
	philo->forks[1] = (philo->id + 1) % philo->table->nb_philos;
}
