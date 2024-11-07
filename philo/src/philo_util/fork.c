/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:50:44 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 12:52:40 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    grab_forks(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    // Always grab the lower-numbered fork first
    if (philo->id % 2 == 0)
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    else
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }

    pthread_mutex_lock(first_fork);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(second_fork);
    print_status(philo, "has taken a fork");
}

void    release_forks(t_philo *philo)
{
    // Release in reverse order of acquisition
    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
    else
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
    }
}
