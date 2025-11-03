/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:19:56 by shunwata          #+#    #+#             */
/*   Updated: 2025/10/20 14:20:47 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void monitor_philos(t_table *table)
{
	int		i;
	bool	philos_not_finished;

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
		philos_not_finished = false;
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
			// 食事回数チェック（num_mealsが設定されている場合のみ）
			if (table->num_meals > 0 && (table->philos[i].eat_count) < (table->num_meals))
				philos_not_finished = true;
			pthread_mutex_unlock(&table->meal_lock.mutex);
			i++;
		}
		// 全哲学者が必要な食事回数に達した場合
		if (table->num_meals > 0 && !philos_not_finished)
		{
			pthread_mutex_lock(&table->death_lock.mutex);
			table->simulation_should_end = 1;
			pthread_mutex_unlock(&table->death_lock.mutex);
			return;
		}
		usleep(100); // CPUを使いすぎないように少し待つ
	}
}
