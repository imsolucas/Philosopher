/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:00:49 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 00:24:24 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_of_philos == 1)
	{
		print_status(philo, "has taken a fork");
		precise_sleep(philo->table->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!*philo->table->someone_died)
	{
		grab_forks(philo);
		handle_eat(philo);
		release_forks(philo);
		handle_sleep(philo);
		handle_think(philo);
		if (philo->table->num_of_meals > 0
			&& philo->meals_eaten >= philo->table->num_of_meals)
			break ;
	}
	return (NULL);
}
