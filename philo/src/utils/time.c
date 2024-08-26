/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:25:18 by geibo             #+#    #+#             */
/*   Updated: 2024/08/17 13:42:05 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	convert_to_ms(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

size_t	get_current_ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (convert_to_ms(time));
}

size_t	get_elapsed_time(size_t start_time)
{
	return (get_current_ms_time() - start_time);
}

void	custom_usleep(size_t activity_time)
{
	size_t	begining_of_usleep;

	begining_of_usleep = get_current_ms_time();
	while ((get_current_ms_time() - begining_of_usleep) < activity_time)
		usleep(50);
}
