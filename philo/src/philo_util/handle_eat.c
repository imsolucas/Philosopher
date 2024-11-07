/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:57:55 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 13:58:48 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->table->print_mutex);
	if (!*philo->table->someone_died)
	{
		philo->last_meal_time = get_time();
		printf("%lld %d is eating\n", philo->last_meal_time
			- ((philo->table->start_time.tv_sec * 1000)
				+ (philo->table->start_time.tv_usec / 1000)), philo->id);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->table->print_mutex);
		precise_sleep(philo->table->time_to_eat);
	}
	else
	{
		pthread_mutex_unlock(philo->table->print_mutex);
	}
}
