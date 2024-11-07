/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:01:00 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 02:05:54 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_sleep(t_philo *philo)
{
	long long	sleep_end_time;
	long long	sleep_die_time;
	long long	sleep_duration;
	long long	current_time;
	
	current_time = get_elapsed_time(philo->table->start_time);
	sleep_end_time = current_time + philo->table->time_to_sleep;
	sleep_die_time = current_time + philo->table->time_to_die;
	print_status(philo, "is sleeping");
	if (sleep_end_time > sleep_die_time)
	{
		sleep_duration = philo->table->time_to_die;
		printf("time to die: %lld\n", philo->table->time_to_die);
		precise_sleep(sleep_duration);
	}
	else
	{
		sleep_duration = philo->table->time_to_sleep;
		precise_sleep(sleep_duration);
	}
}

void	handle_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	handle_death(t_philo *philo)
{
	long long	time_to_sleep;
	long long	time_to_die;

	time_to_sleep = philo->table->time_to_sleep;
	time_to_die = philo->table->time_to_die;
	if (time_to_sleep > time_to_die)
	{
		print_status(philo, "died");
		pthread_exit(0);
	}
}
