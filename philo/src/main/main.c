/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:58:46 by geibo             #+#    #+#             */
/*   Updated: 2024/08/17 00:48:21 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	arg_check(argc, argv);
	table = init_philo(table, argc, argv);
	set_up_tables(table);
	table->philos = set_up_philos(table);
	manage_threads(table->philos, table);
	free_mutex(table);
	free_table(table);
}
