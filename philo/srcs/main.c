/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:55:08 by shunwata          #+#    #+#             */
/*   Updated: 2025/11/13 18:22:50 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (!is_valid_args(argc, argv))
		return (1);
	if (!init_table(&table, argv) != 0)
		return (cleanup(&table), 1);
	table.start_time = get_time();
	i = 0;
	while (i < table.num_philos)
		(pthread_create(&table.philos[i].thread, NULL, \
			&philo_routine, &table.philos[i]), i++);
	monitor_philos(&table);
	i = 0;
	while (i < table.num_philos)
		pthread_join(table.philos[i++].thread, NULL);
	cleanup(&table);
	return (0);
}
