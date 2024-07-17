/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:17:20 by geibo             #+#    #+#             */
/*   Updated: 2024/07/17 22:24:52 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{

}

void	create_threads(t_philo **philo, t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (!pthread_create(&philo[i]->thread, NULL, philo_routine, (void *)philo[i]))
		{
			printf("Error: pthread_create failed\n");
		}
	}
}

void	manage_threads(t_philo **philo, t_table *table)
{
	gettimeofday(&table->start_time, NULL);

}
