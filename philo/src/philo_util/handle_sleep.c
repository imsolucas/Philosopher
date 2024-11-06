/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:01:00 by geibo             #+#    #+#             */
/*   Updated: 2024/11/06 23:01:21 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	precise_sleep(philo->table->time_to_sleep);
}

void	handle_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}
