/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:58:39 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 13:58:14 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table
{
	int				num_of_philos;
	int				num_of_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*print_mutex;
	bool			*someone_died;
	struct timeval	start_time;
	pthread_t		*threads;
}					t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*forks;
	t_table			*table;
}					t_philo;

// libft
int					ft_atoi(const char *str);
int					ft_strcmp(const char *s1, const char *s2);

// utils
void				arg_check(int argc);
void				set_zero(t_table *table);
t_table				*set_up_table(int argc, char **argv);
long long			get_time(void);
t_philo				*init_philo(t_table *table);
void				sitting(t_philo *philos);
void				precise_sleep(int ms);
void				print_status(t_philo *philo, char *status);
void				clean_up_tables(t_philo *philos, t_table *table);
void				assign_forks(t_philo *philos, pthread_mutex_t *forks,
						pthread_mutex_t *print_mutex);
t_table				*alloc_table(void);
void				init_table_values(t_table *table, int argc, char **argv);

// philo_util
void				create_threads(t_philo *philo, pthread_t *threads);
void				join_threads(t_philo *philo, pthread_t *threads,
						pthread_t monitor_threads);
void				manage_threads(t_philo *philo);
void				*philo_routine(void *arg);
void				handle_sleep(t_philo *philo);
void				handle_think(t_philo *philo);
void				handle_eat(t_philo *philo);
void				grab_forks(t_philo *philo);
void				release_forks(t_philo *philo);
void				*monitor_thread(void *arg);

#endif