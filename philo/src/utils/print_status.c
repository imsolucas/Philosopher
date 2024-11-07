/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:39:36 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 01:29:43 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->table->print_mutex);
	if (!*philo->table->someone_died)
	{
		printf("%lld %d %s\n", get_elapsed_time(philo[0].table->start_time),
			philo->id, status);
	}
	if (ft_strcmp(status, "died") == 0)
		*philo->table->someone_died = true;
	pthread_mutex_unlock(philo->table->print_mutex);
}
