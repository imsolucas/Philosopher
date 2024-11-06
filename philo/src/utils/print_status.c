/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:39:36 by geibo             #+#    #+#             */
/*   Updated: 2024/11/06 17:39:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(philo->table->print_mutex);
    if (!*philo->table->someone_died)
    {
        printf("%lld %d %s\n", get_time() - 
            ((philo->table->start_time.tv_sec * 1000) + 
            (philo->table->start_time.tv_usec / 1000)), 
            philo->id, status);
    }
    pthread_mutex_unlock(philo->table->print_mutex);
}
