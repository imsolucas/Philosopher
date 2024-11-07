/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:03:35 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 13:58:42 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_philosopher_death(t_philo *philo, size_t i)
{
	long long	current_time;

	current_time = get_time();
	if (current_time - philo[i].last_meal_time > philo[i].table->time_to_die)
	{
		if (!*philo[0].table->someone_died)
		{
			printf("%lld %d died\n", current_time
				- ((philo[0].table->start_time.tv_sec * 1000)
					+ (philo[0].table->start_time.tv_usec / 1000)),
				philo[i].id);
			*philo[0].table->someone_died = true;
		}
		return (true);
	}
	return (false);
}

static bool	check_all_ate(t_philo *philo)
{
	size_t	i;
	bool	all_ate;

	i = 0;
	all_ate = true;
	while (i < (size_t)philo[0].table->num_of_philos)
	{
		if (philo->table->num_of_meals > 0
			&& philo[i].meals_eaten < philo->table->num_of_meals)
			all_ate = false;
		i++;
	}
	return (all_ate);
}

static bool	monitor_status(t_philo *philo)
{
	size_t	i;
	bool	should_exit;

	i = 0;
	should_exit = false;
	pthread_mutex_lock(philo[0].table->print_mutex);
	if (*philo[0].table->someone_died)
	{
		pthread_mutex_unlock(philo[0].table->print_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo[0].table->print_mutex);
	while (i < (size_t)philo[0].table->num_of_philos)
	{
		pthread_mutex_lock(philo[0].table->print_mutex);
		should_exit = check_philosopher_death(philo, i);
		pthread_mutex_unlock(philo[0].table->print_mutex);
		if (should_exit)
			return (true);
		i++;
	}
	return (false);
}

void	*monitor_thread(void *arg)
{
	t_philo	*philo;
	bool	should_exit;

	philo = (t_philo *)arg;
	while (1)
	{
		should_exit = monitor_status(philo);
		if (should_exit)
			return (NULL);
		pthread_mutex_lock(philo[0].table->print_mutex);
		if (philo->table->num_of_meals > 0 && check_all_ate(philo)
			&& !*philo[0].table->someone_died)
		{
			*philo[0].table->someone_died = true;
			pthread_mutex_unlock(philo[0].table->print_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(philo[0].table->print_mutex);
		usleep(1000);
	}
	return (NULL);
}
