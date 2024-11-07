/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:55:47 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 04:24:12 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_thread(void *arg)
{
	t_philo		*philo;
	size_t		i;
	long long	last_meal_time;
	long long	time_since_last_meal;
	long long	meals_eaten;
	long long	count;
	long long	num_of_time_to_eat;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		count = 0;
		if (philo[0].table->num_of_philos == 1)
			return ;
		while (i < (size_t)philo[0].table->num_of_philos)
		{
			pthread_mutex_lock(&philo[0].table->last_meal_mutex[i]);
			last_meal_time = philo[i].last_meal_time;
			pthread_mutex_unlock(&philo[0].table->last_meal_mutex[i]);
			time_since_last_meal = get_elapsed_time(philo[0].table->start_time)
				- last_meal_time;
			if (time_since_last_meal > philo[0].table->time_to_die)
			{
				print_status(&philo[i], "died");
				return ;
			}
			i++;
		}
		i = 0;
		num_of_time_to_eat = philo[0].table->num_of_meals;
		while (i < (size_t)philo[0].table->num_of_philos)
		{
			pthread_mutex_lock(philo[0].table->meals_eaten_mutex);
			meals_eaten = philo[i].meals_eaten;
			pthread_mutex_unlock(philo[0].table->meals_eaten_mutex);
			if (num_of_time_to_eat != 0 && meals_eaten >= philo[0].table->num_of_meals)
				count++;
			i++;
		}
		if (count == philo[0].table->num_of_philos)
		{
			pthread_mutex_lock(philo[0].table->print_mutex);
			*philo[0].table->someone_died = true;
			pthread_mutex_unlock(philo[0].table->print_mutex);
			return ;
		}
		usleep(50);
	}
}
