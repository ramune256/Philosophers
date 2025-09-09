/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:09:14 by shunwata          #+#    #+#             */
/*   Updated: 2025/09/09 21:48:48 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 哲学者のライフサイクル
void *philo_routine(void *arg)
{
	t_philo *philo;
	t_table *table;
	int 	left_fork;
	int 	right_fork;

	philo = (t_philo *)arg;
	table = philo->table;
	left_fork = philo->id - 1;
	right_fork = philo->id % table->num_philos;

	// (任意) スタートタイミングをずらす
	if (philo->id % 2 != 0)
		usleep(100);

	while (1) // まだ無限ループ
	{
		// 食事アクション
		if (philo->id % 2 == 0)
		{
			// 偶数IDの哲学者：左 → 右 の順で取る
			pthread_mutex_lock(&table->forks[left_fork]);
			printf("%lld %d has taken a fork\n", get_time() - table->start_time, philo->id);
			pthread_mutex_lock(&table->forks[right_fork]);
			printf("%lld %d has taken a fork\n", get_time() - table->start_time, philo->id);
		}
		else
		{
			// 奇数IDの哲学者：右 → 左 の順で取る
			pthread_mutex_lock(&table->forks[right_fork]);
			printf("%lld %d has taken a fork\n", get_time() - table->start_time, philo->id);
			pthread_mutex_lock(&table->forks[left_fork]);
			printf("%lld %d has taken a fork\n", get_time() - table->start_time, philo->id);
		}

		printf("%lld %d is eating\n", get_time() - table->start_time, philo->id);
		// 食事開始時刻を記録
        pthread_mutex_lock(&table->meal_lock);
		philo->last_meal_time = get_time();
        philo->eat_count++;
        pthread_mutex_unlock(&table->meal_lock);

		usleep(table->time_to_eat * 1000);

		pthread_mutex_unlock(&table->forks[left_fork]);
		pthread_mutex_unlock(&table->forks[right_fork]);

		// 睡眠と思考アクション
		printf("%lld %d is sleeping\n", get_time() - table->start_time, philo->id);
		usleep(table->time_to_sleep * 1000);
		printf("%lld %d is thinking\n", get_time() - table->start_time, philo->id);
	}
	return (NULL);
}
