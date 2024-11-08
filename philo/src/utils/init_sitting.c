/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sitting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:53:21 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 09:38:21 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_basic_mutexes(t_philo *philos, t_mutex_set *mutex_set)
{
	pthread_mutex_init(mutex_set->print_mutex, NULL);
	pthread_mutex_init(mutex_set->meals_eaten_mutex, NULL);
}

static void	init_philo_mutexes(t_philo *philos, t_mutex_set *mutex_set)
{
	size_t	i;

	i = 0;
	while (i < (size_t)philos[0].table->num_of_philos)
	{
		pthread_mutex_init(&mutex_set->forks[i], NULL);
		pthread_mutex_init(&mutex_set->last_meal_mutex[i], NULL);
		i++;
	}
}

static void	assign_mutexes_to_philos(t_philo *philos, t_mutex_set *mutex_set)
{
	size_t	i;

	i = 0;
	while (i < (size_t)philos->table->num_of_philos)
	{
		philos[i].left_fork = &mutex_set->forks[i];
		philos[i].right_fork = &mutex_set->forks[(i + 1)
			% philos->table->num_of_philos];
		philos[i].table->print_mutex = mutex_set->print_mutex;
		philos[i].table->last_meal_mutex = mutex_set->last_meal_mutex;
		philos[i].table->meals_eaten_mutex = mutex_set->meals_eaten_mutex;
		philos[i].forks = mutex_set->forks;
		i++;
	}
}

static bool	alloc_mutexes(t_philo *philos, t_mutex_set *mutex_set)
{
	mutex_set->forks = malloc(sizeof(pthread_mutex_t)
			* philos->table->num_of_philos);
	mutex_set->last_meal_mutex = malloc(sizeof(pthread_mutex_t)
			* philos->table->num_of_philos);
	mutex_set->print_mutex = malloc(sizeof(pthread_mutex_t));
	mutex_set->meals_eaten_mutex = malloc(sizeof(pthread_mutex_t));
	if (!mutex_set->forks || !mutex_set->print_mutex
		|| !mutex_set->last_meal_mutex || !mutex_set->meals_eaten_mutex)
		return (false);
	return (true);
}

void	sitting(t_philo *philos)
{
	t_mutex_set	mutex_set;

	if (!alloc_mutexes(philos, &mutex_set))
	{
		printf("Error: malloc failed\n");
		free(mutex_set.forks);
		free(mutex_set.print_mutex);
		free(mutex_set.last_meal_mutex);
		free(mutex_set.meals_eaten_mutex);
		free(philos[0].table);
		free(philos);
		exit(-1);
	}
	init_basic_mutexes(philos, &mutex_set);
	init_philo_mutexes(philos, &mutex_set);
	assign_mutexes_to_philos(philos, &mutex_set);
}
