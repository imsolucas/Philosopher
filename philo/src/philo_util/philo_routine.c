/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:00:49 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 14:11:55 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	should_continue_routine(t_philo *philo)
{
	bool	continue_flag;

	pthread_mutex_lock(philo->table->print_mutex);
	continue_flag = (!*philo->table->someone_died
			&& (philo->table->num_of_meals == 0
				|| philo->meals_eaten < philo->table->num_of_meals));
	pthread_mutex_unlock(philo->table->print_mutex);
	return (continue_flag);
}

static bool	handle_single_philo(t_philo *philo)
{
	if (philo->table->num_of_philos == 1)
	{
		print_status(philo, "has taken a fork");
		print_status(philo, "died");
		return (true);
	}
	return (false);
}

static bool	philo_actions(t_philo *philo)
{
	if (grab_forks(philo) == false)
		return (false);
	handle_eat(philo);
	release_forks(philo);
	handle_sleep(philo);
	handle_death(philo);
	handle_think(philo);
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (handle_single_philo(philo))
		return (NULL);
	if (philo->id % 2 == 0)
		precise_sleep(100);
	while (1)
	{
		if (philo_actions(philo) == false)
			return (NULL);
	}
	return (NULL);
}
