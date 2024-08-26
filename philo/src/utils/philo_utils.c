/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:04:48 by geibo             #+#    #+#             */
/*   Updated: 2024/08/22 07:18:00 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_up_tables(t_table *table)
{
	table->forks_mutex = create_mutex(table->nb_philos);
	table->last_meal_time_lock = create_mutex(table->nb_philos);
	table->stop_print_lock = create_mutex(1);
	table->log_mutex = create_mutex(1);
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

static void	print_activity(t_philo *philo, t_table *table,
	char *activity, size_t start_time)
{
	if (ft_strcmp(activity, "fork") == 0)
	{
		printf("%llu %u has taken a fork\n", 
			get_elapsed_time(start_time),
			philo->id
			);
	}
	else if (ft_strcmp(activity, "died") == 0)
	{
		printf("%llu %u died\n",
			get_elapsed_time(start_time),
			philo->id
			);
		table->stop_printing = true;
	}
	else
	{
		printf("%llu %u %s\n",
			get_elapsed_time(start_time),
			philo->id,
			activity
			);
	}
}

void	write_activity(t_philo *philo, t_table *table, 
	char *activity, size_t start_time)
{
	pthread_mutex_lock(table->log_mutex);
	pthread_mutex_lock(table->stop_print_lock);
	if (!table->stop_printing)
		print_activity(philo, table, activity, start_time);
	pthread_mutex_unlock(table->stop_print_lock);
	pthread_mutex_unlock(table->log_mutex);
}
