/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:57:55 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 09:17:57 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->last_meal_mutex[philo->id - 1]);
	philo->last_meal_time = get_elapsed_time(philo->table->start_time);
	pthread_mutex_unlock(&philo->table->last_meal_mutex[philo->id - 1]);
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->table->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->table->meals_eaten_mutex);
	precise_sleep(philo->table->time_to_eat);
}
