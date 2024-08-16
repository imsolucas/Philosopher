/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:58:39 by geibo             #+#    #+#             */
/*   Updated: 2024/08/17 00:11:14 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	unsigned int		id;
	unsigned int		forks[2];
	pthread_t			thread;
	t_table				*table;
	unsigned long long	total_meals;
	unsigned long long	last_meal_time;
}	t_philo;

typedef struct s_table
{
	t_philo				**philos;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	pthread_mutex_t		*last_meal_time_lock;
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		*stop_print_lock;
	pthread_mutex_t		*die_lock;
	pthread_mutex_t		*eating_counter_lock;
	bool				*stop_printing;
	struct timeval		start_time;
	unsigned int		nb_philos;
	unsigned int		nb_meals;
	size_t				*forks;
	size_t				time;
}	t_table;

// libft
int		ft_atoi(const char *str);

// utils
void	arg_check(int argc, char **argv);
t_table	*set_zero(t_table *table);
t_table	*init_philo(t_table *table, int argc, char **argv);
t_philo	**set_up_philos(t_table *table);
static void	assign_forks(t_philo *philo);

// debug
void	error_exit(char *str);
void	debug(t_table *table);
void	free_table(t_table *table);
void	free_mutex(t_table *table);

// philo_utils
static bool	initialize_mutex(pthread_mutex_t **mutex, t_table *table);
static	pthread_mutex_t	*create_mutex(size_t size);
void	set_up_tables(t_table *table);
void	set_up_forks(t_table *table);
void	free_mutex(t_table *table);

//philo
void	*philo_routine(void *arg);
void	create_threads(t_philo **philo, t_table *table);
void	join_threads(t_philo **philo, t_table *table);
void	manage_threads(t_philo **philo, t_table *table);

// time
size_t	get_current_ms_time(void);
size_t	convert_to_ms(struct timeval time);
size_t	get_elapsed_time(size_t start_time);

//philo routine
void	grab_forks(t_philo *philo, t_table *table);
void	handle_eat(t_philo *philo, t_table *table);
void	release_forks(t_philo *philo, t_table *table);
void	sleeping(t_philo *philo, t_table *table);
void	die(t_philo *philo, t_table *table);
void	thinking(t_philo *philo, t_table *table);

// monitor_threads
void	monitor_threads(t_philo **philo, t_table *table);

#endif