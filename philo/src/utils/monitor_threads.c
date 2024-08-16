/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:35:39 by geibo             #+#    #+#             */
/*   Updated: 2024/08/17 00:10:36 by geibo            ###   ########.fr       */
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
			philo[i]->table->stop_printing = true;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_exit_condition(t_philo *philo)
{
	size_t	total_meal_count;
	size_t	nb_meals;
	bool	stop_printing;

	nb_meals = philo->table->nb_meals;
	pthread_mutex_lock(&philo->table->eating_counter_lock[philo->id]);
	total_meal_count = philo->total_meals;
	pthread_mutex_unlock(&philo->table->eating_counter_lock[philo->id]);
	pthread_mutex_lock(philo->table->stop_print_lock);
	stop_printing = philo->table->stop_printing;
	pthread_mutex_unlock(philo->table->stop_print_lock);
	if (stop_printing)
		return (true);
	return (nb_meals != -1 && total_meal_count >= nb_meals);
}

bool	check_eating_counter(t_philo *philo)
{
	size_t	i;
	size_t	counter;
	size_t	nb_philos;

	i = 0;
	counter = 0;
	nb_philos = philo->table->nb_philos;
	while (i < nb_philos)
	{
		if (check_exit_condition(philo))
			counter++;
		i++;
	}
	if (counter == nb_philos)
	{
		pthread_mutex_lock(philo->table->stop_print_lock);
		philo->table->stop_printing = true;
		pthread_mutex_unlock(philo->table->stop_print_lock);
		return (true);
	}
	return (false);
}

void	monitor_threads(t_philo **philo, t_table *table)
{
	size_t	i;

	while (1)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (check_last_meal_time(table, philo))
				return ;
			else if (check_eating_counter(philo[i]))
				return ;
			usleep(50);
			i++;
		}
	}
}
