/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:22:10 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 01:01:33 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	get_elapsed_time(struct timeval start)
{
	long long	start_in_ms;

	start_in_ms = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (get_time() - start_in_ms);
}

void	precise_sleep(int ms)
{
	long long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}
