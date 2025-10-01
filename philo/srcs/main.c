/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:55:08 by shunwata          #+#    #+#             */
/*   Updated: 2025/10/01 21:08:54 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_args(int argc, char **argv)
{
	// ここに引数の数や内容（数字か、正の数か）をチェックする処理を追加
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (0);
	}
	return (1);
}

void monitor_philos(t_table *table)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&table->death_lock.mutex);
		if (table->simulation_should_end)
		{
			pthread_mutex_unlock(&table->death_lock.mutex);
			break;
		}
		pthread_mutex_unlock(&table->death_lock.mutex);
		i = 0;
		while (i < table->num_philos)
		{
			pthread_mutex_lock(&table->meal_lock.mutex);
			if ((get_time() - table->philos[i].last_meal_time) > (table->time_to_die))
			{
				print_status(&table->philos[i], "died");
				pthread_mutex_lock(&table->death_lock.mutex);
				table->simulation_should_end = 1;
				pthread_mutex_unlock(&table->death_lock.mutex);
				pthread_mutex_unlock(&table->meal_lock.mutex);
				return ;
			}
			pthread_mutex_unlock(&table->meal_lock.mutex);
			i++;
		}
		usleep(100); // CPUを使いすぎないように少し待つ
	}
}

int main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (!is_valid_args(argc, argv))
		return (1);
	if (init_table(&table, argv) != 0)
		return (cleanup(&table), 1);
	table.start_time = get_time();
	i = 0;
	while (i < table.num_philos)
		pthread_create(&table.philos[i].thread, NULL, &philo_routine, &table.philos[i++]);
	monitor_philos(&table);
	i = 0;
	while (i < table.num_philos)
		pthread_join(table.philos[i++].thread, NULL);
	cleanup(&table);
	return (0);
}
