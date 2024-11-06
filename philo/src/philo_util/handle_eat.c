/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:57:55 by geibo             #+#    #+#             */
/*   Updated: 2024/11/06 23:00:24 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_eat(t_philo *philo)
{
	print_status(philo, "is eating");
	philo->last_meal_time = get_time();
	precise_sleep(philo->table->time_to_eat);
	philo->meals_eaten++;
}
