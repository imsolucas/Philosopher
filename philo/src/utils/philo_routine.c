/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 01:58:48 by geibo             #+#    #+#             */
/*   Updated: 2024/08/26 15:26:46 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo *philo, t_table *table)
{
	if (table->nb_philos == 1)
	{
		printf("%llu %u has taken a fork\n", get_elapsed_time(table->time), philo->id);
		pthread_exit(0);
	}
	pthread_mutex_lock(&table->forks_mutex[philo->id]);
	printf("%llu %u has taken a fork\n", get_elapsed_time(table->time), philo->id);
	pthread_mutex_lock(&table->forks_mutex[(philo->id + 1) % philo->table->nb_philos]);
	printf("%llu %u has taken a fork\n", get_elapsed_time(table->time), philo->id);
	pthread_mutex_lock(philo->table->stop_print_lock);
	table->forks[philo->id] = 0;
	table->forks[(philo->id + 1) % philo->table->nb_philos] = 0;
	if (philo->table->stop_printing)
	{
		pthread_mutex_unlock(philo->table->stop_print_lock);
		release_forks(philo, table);
		pthread_exit(0);
	}
	pthread_mutex_unlock(philo->table->stop_print_lock);
}

void	handle_eat(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->last_meal_time_lock[philo->id]);
	philo->last_meal_time = get_elapsed_time(table->time);
	pthread_mutex_unlock(&table->last_meal_time_lock[philo->id]);
	printf("%llu %u is eating\n", philo->last_meal_time, philo->id);
	pthread_mutex_lock(&table->eating_counter_lock[philo->id]);
	philo->total_meals++;
	pthread_mutex_unlock(&table->eating_counter_lock[philo->id]);
	custom_usleep(philo->table->time_to_eat);
}

void	release_forks(t_philo *philo, t_table *table)
{
	pthread_mutex_unlock(&table->forks_mutex[philo->id]);
	pthread_mutex_unlock(&table->forks_mutex[(philo->id + 1) % philo->table->nb_philos]);
	table->forks[philo->id] = 1;
	table->forks[(philo->id + 1) % philo->table->nb_philos] = 1;
}

void	sleeping(t_philo *philo, t_table *table)
{
	size_t	time_to_sleep;
	size_t	time_to_die;
	size_t	sleep_duration;
	
	time_to_sleep = table->time_to_sleep;
	time_to_die = table->time_to_die;
	if (time_to_sleep > time_to_die)
	{
		sleep_duration = table->time_to_die;
		printf("%llu %u sleeping\n", get_elapsed_time(table->time), philo->id);
		custom_usleep(sleep_duration);
	}
	else
	{
		sleep_duration = table->time_to_sleep;
		printf("%llu %u is sleeping\n", get_elapsed_time(table->time), philo->id);
		custom_usleep(sleep_duration);
	}
}

void	die(t_philo *philo, t_table *table)
{
	size_t	time_to_die;
	size_t	time_to_sleep;

	time_to_die = table->time_to_die;
	time_to_sleep = table->time_to_sleep;
	if (time_to_sleep > time_to_die)
	{
		printf("%llu %u died\n", get_elapsed_time(table->time), philo->id);
		pthread_exit(0);
	}
}

void	thinking(t_philo *philo, t_table *table)
{
	printf("%llu %u is thinking\n", get_elapsed_time(table->time), philo->id);
}
