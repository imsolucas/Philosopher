/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:00:49 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 01:53:34 by geibo            ###   ########.fr       */
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
		usleep(philo->table->time_to_die * 1000);
		return (true);
	}
	return (false);
}

static void	philo_actions(t_philo *philo)
{
	grab_forks(philo);
	handle_eat(philo);
	release_forks(philo);
	pthread_mutex_lock(philo->table->print_mutex);
	// if (*philo->table->someone_died)
	// {
	// 	pthread_mutex_unlock(philo->table->print_mutex);
	// 	return ;
	// }
	pthread_mutex_unlock(philo->table->print_mutex);
	handle_sleep(philo);
	handle_death(philo);
	handle_think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (handle_single_philo(philo))
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
		philo_actions(philo);
	return (NULL);
}
