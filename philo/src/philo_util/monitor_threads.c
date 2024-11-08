/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:55:47 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 16:24:15 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_philo_death(t_philo *philo)
{
	struct timeval	start_time;
	long long		last_meal_time;
	long long		i;
	long long		elapsed_time;
	long long		time_since_last_meal;

	start_time = philo[0].table->start_time;
	i = 0;
	while (i < (size_t)philo[0].table->num_of_philos)
	{
		pthread_mutex_lock(&philo[0].table->last_meal_mutex[i]);
		last_meal_time = philo[i].last_meal_time;
		pthread_mutex_unlock(&philo[0].table->last_meal_mutex[i]);
		elapsed_time = get_elapsed_time(start_time);
		time_since_last_meal = (elapsed_time - last_meal_time);
		if (time_since_last_meal > philo[0].table->time_to_die)
		{
			print_status(&philo[i], "died");
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	check_all_meals_eaten(t_philo *philo)
{
	size_t		i;
	long long	meals_eaten;
	long long	count;

	i = 0;
	count = 0;
	while (i < (size_t)philo[0].table->num_of_philos)
	{
		pthread_mutex_lock(philo[0].table->meals_eaten_mutex);
		meals_eaten = philo[i].meals_eaten;
		pthread_mutex_unlock(philo[0].table->meals_eaten_mutex);
		if (philo[0].table->num_of_meals != 0
			&& meals_eaten >= philo[0].table->num_of_meals)
			count++;
		i++;
	}
	return (count == philo[0].table->num_of_philos);
}

static void	handle_all_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(philo[0].table->print_mutex);
	*philo[0].table->someone_died = true;
	pthread_mutex_unlock(philo[0].table->print_mutex);
}

static bool	monitor_philos(t_philo *philo)
{
	if (philo[0].table->num_of_philos == 1)
		return (true);
	if (check_all_meals_eaten(philo))
	{
		handle_all_meals_eaten(philo);
		return (true);
	}
	return (false);
}

static int	check_philo_last_meal_time(t_philo *philo)
{
}

void	monitor_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_philo_death(philo))
			return ;
		if (monitor_philos(philo))
			return ;
		usleep(50);
	}
}
