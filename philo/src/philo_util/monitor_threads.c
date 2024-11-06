/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:03:35 by geibo             #+#    #+#             */
/*   Updated: 2024/11/06 17:38:21 by codespace        ###   ########.fr       */
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

void *monitor_thread(void *arg)
{
    t_philo     *philo;
    size_t      i;
    long long   current_time;
    bool        all_ate;

    philo = (t_philo *)arg;
    while (1)
    {
        i = 0;
        all_ate = true;
        while (i < (size_t)philo[0].table->num_of_philos && !*philo[0].table->someone_died)
        {
            current_time = get_time();
            if (current_time - philo[i].last_meal_time > philo[i].table->time_to_die)
            {
                pthread_mutex_lock(philo[0].table->print_mutex);
                if (!*philo[0].table->someone_died)
                    printf("%lld %d died\n", current_time - ((philo[0].table->start_time.tv_sec * 1000)
                        + (philo[0].table->start_time.tv_usec / 1000)), philo[i].id);
                *philo[0].table->someone_died = true;
                pthread_mutex_unlock(philo[0].table->print_mutex);
                return (NULL);
            }
            if (philo->table->num_of_meals > 0 && 
                philo[i].meals_eaten < philo->table->num_of_meals)
                all_ate = false;
            i++;
        }
        if (philo->table->num_of_meals > 0 && all_ate)
        {
            *philo[0].table->someone_died = true;
            return (NULL);
        }
        usleep(100);
    }
    return (NULL);
}
