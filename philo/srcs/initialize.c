/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:00:34 by shunwata          #+#    #+#             */
/*   Updated: 2025/09/08 18:32:00 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// プログラム全体(table)を初期化
int init_table(t_table *table, char **argv)
{
	int	i;

	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->num_meals_required = ft_atoi(argv[5]);
	else
		table->num_meals_required = -1; // -1は食事回数制限なしを示す
	table->simulation_should_end = 0;

	// Mutexの初期化
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < (table->num_philos))
		pthread_mutex_init(&table->forks[i++], NULL);
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->death_lock, NULL);

	// 哲学者たちの初期化
	table->philos = malloc(sizeof(t_philo) * (table->num_philos));
	if (!table->philos)
		return (1); //table->forksもフリーすべき mutexも？
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
