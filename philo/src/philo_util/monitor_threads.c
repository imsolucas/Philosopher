/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:03:35 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 00:16:02 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(t_philo *philo, size_t i, long long current_time)
{
	if (current_time - philo[i].last_meal_time > philo[i].table->time_to_die)
	{
		pthread_mutex_lock(philo[0].table->print_mutex);
		printf("%lld %d died\n", current_time
			- ((philo[0].table->start_time.tv_sec * 1000)
				+ (philo[0].table->start_time.tv_usec / 1000)), philo[i].id);
		*philo[0].table->someone_died = true;
		pthread_mutex_unlock(philo[0].table->print_mutex);
		return (true);
	}
	return (false);
}

void	*monitor_thread(void *arg)
{
	t_philo		*philo;
	size_t		i;
	long long	current_time;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo[0].table->num_of_philos)
		{
			current_time = get_time();
			if (check_death(philo, i, current_time))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
