/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:58:46 by geibo             #+#    #+#             */
/*   Updated: 2024/07/17 22:38:08 by geibo            ###   ########.fr       */
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
	debug(table);
	free_table(table);
}
