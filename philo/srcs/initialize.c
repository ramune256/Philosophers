/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:00:34 by shunwata          #+#    #+#             */
/*   Updated: 2025/10/01 20:19:30 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init_manage(t_mutex_combo *mutex_combo, t_table *table)
{
	if (pthread_mutex_init(&mutex_combo->mutex, NULL))
	{
		mutex_combo->is_initialized = false;
		table->alloc_failed = true;
		return (1);
	}
	mutex_combo->is_initialized = true;
	return (0);
}

int	init_table(t_table *table, char **argv)
{
	int	i;

	memset(table, 0, sizeof(table));
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->num_meals_required = ft_atoi(argv[5]);
	else
		table->num_meals_required = -1;
	table->simulation_should_end = false;
	table->forks = malloc(sizeof(t_mutex_combo) * table->num_philos);
	table->philos = malloc(sizeof(t_philo) * (table->num_philos));
	if (!table->forks || !table->philos)
		return (1);
	i = 0;
	while (i < (table->num_philos))
		(mutex_init_manage(&table->forks[i], table), i++);
	mutex_init_manage(&table->write_lock, table);
	mutex_init_manage(&table->meal_lock, table);
	mutex_init_manage(&table->death_lock, table);
	if (table->alloc_failed)
		return (1);
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].last_meal_time = get_time();
		table->philos[i].table = table;
		i++;
	}
	return (0);
}
