/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:12:23 by geibo             #+#    #+#             */
/*   Updated: 2024/11/07 00:35:12 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	arg_check(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		printf("Usage: ./philo <arg1> <arg2> <arg3> <arg4> [arg5]\n");
		printf("arg1: number of philosophers\n");
		printf("arg2: time to die in ms\n");
		printf("arg3: time to eat in ms\n");
		printf("arg4: time to sleep in ms\n");
		printf("arg5: [number_of_times_each_philosopher_must_eat](optional)\n");
		exit(-1);
	}
}
