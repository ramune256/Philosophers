/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:55:08 by shunwata          #+#    #+#             */
/*   Updated: 2025/09/08 18:13:07 by shunwata         ###   ########.fr       */
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
	while (1)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->simulation_should_end)
		{
			pthread_mutex_unlock(&table->death_lock);
			break;
		}
		pthread_mutex_unlock(&table->death_lock);

		for (int i = 0; i < table->num_philos; i++)
		{
			pthread_mutex_lock(&table->meal_lock);
			// 最後の食事からtime_to_die以上経過していたら死亡
			if ((get_time() - table->philos[i].last_meal_time) > (table->time_to_die))
			{
				// printf("%lld %d died\n", get_time() - table->start_time, table->philos[i].id);
				print_status(&table->philos[i], "died");
				pthread_mutex_lock(&table->death_lock);
				table->simulation_should_end = 1;
				pthread_mutex_unlock(&table->death_lock);
				pthread_mutex_unlock(&table->meal_lock);
				return;
			}
			pthread_mutex_unlock(&table->meal_lock);
		}
		usleep(100); // CPUを使いすぎないように少し待つ
	}
}


int main(int argc, char **argv)
{
	t_table	table;

	if (!is_valid_args(argc, argv))
		return (1);
	if (init_table(&table, argv) != 0)
		return (1);

	table.start_time = get_time();
	for (int i = 0; i < table.num_philos; i++)
	{
		// 各哲学者のスレッドを作成
		pthread_create(&table.philos[i].thread, NULL, &philo_routine, &table.philos[i]);
	}
	monitor_philos(&table);
	for (int i = 0; i < table.num_philos; i++)
	{
		// 各哲学者のスレッドが終了するのを待つ
		pthread_join(table.philos[i].thread, NULL);
	}

	cleanup(&table);
	return (0);
}
