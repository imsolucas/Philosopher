/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:39:27 by geibo             #+#    #+#             */
/*   Updated: 2024/11/08 00:36:52 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo	*philos;

	arg_check(argc);
	table = set_up_table(argc, argv);
	if (table->num_of_philos < 1 || table->num_of_philos > 200)
	{
		printf("Error: Number of philosophers must be between 1 and 200\n");
		free(table->someone_died);
		free(table);
		return (1);
	}
	if (!table)
		return (1);
	philos = init_philo(table);
	if (!philos)
	{
		free(table->someone_died);
		free(table);
		return (1);
	}
	sitting(philos);
	manage_threads(philos);
	clean_up_tables(philos, table);
	return (0);
}
