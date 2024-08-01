/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:35:39 by geibo             #+#    #+#             */
/*   Updated: 2024/08/01 18:15:50 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_last_meal_time(t_table *table, t_philo **philo)
{
	struct timeval	start_time;
	size_t			last_meal_time;
	size_t			elapsed_time;
	size_t			i;
	size_t			el_last_meal_time;

	i = 0;
	start_time = table->start_time;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->last_meal_time_lock[i]);
		last_meal_time = philo[i]->last_meal_time;
		pthread_mutex_unlock(&table->last_meal_time_lock[i]);
		elapsed_time = get_elapsed_time(table->time);
		el_last_meal_time = elapsed_time - last_meal_time;
		if (el_last_meal_time > table->time_to_die)
		{
			printf("%zu %zu died\n", el_last_meal_time, philo[i]->id);
			return (true);
		}
		i++;
	}
	return (false);
}

void	monitor_threads(t_philo **philo, t_table *table)
{
	while (1)
	{
		if (check_last_meal_time(table, philo))
			break ;
		usleep(50);
	}
}
