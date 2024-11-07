/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:55:47 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 01:41:23 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_thread(void *arg)
{
	t_philo		*philo;
	size_t		i;
	long long	last_meal_time;
	long long	time_since_last_meal;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
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
		}
	}
}
