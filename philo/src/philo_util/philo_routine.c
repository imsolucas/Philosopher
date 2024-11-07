/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:00:49 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 12:52:58 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->table->num_of_philos == 1)
    {
        print_status(philo, "has taken a fork");
        usleep(philo->table->time_to_die * 1000);
        return (NULL);
    }
    
    // Add a small delay for even-numbered philosophers
    // This helps prevent all philosophers from trying to grab forks simultaneously
    if (philo->id % 2 == 0)
        usleep(1000);

    while (!*philo->table->someone_died &&
           (philo->table->num_of_meals == 0 || 
            philo->meals_eaten < philo->table->num_of_meals))
    {
        grab_forks(philo);
        handle_eat(philo);
        release_forks(philo);
        if (*philo->table->someone_died)
            break;
        handle_sleep(philo);
        if (*philo->table->someone_died)
            break;
        handle_think(philo);
    }
    return (NULL);
}
