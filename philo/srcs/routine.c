/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:09:14 by shunwata          #+#    #+#             */
/*   Updated: 2025/09/08 18:11:18 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 哲学者のライフサイクル
void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_table *table = philo->table;
	int left_fork = philo->id - 1;
	int right_fork = philo->id % table->num_philos;

	while (1) // この時点では無限ループ
	{
		// 食事
		pthread_mutex_lock(&table->forks[left_fork]);
		printf("%lld %d has taken a fork\n", get_time() - table->start_time, philo->id);
		pthread_mutex_lock(&table->forks[right_fork]);
		printf("%lld %d has taken a fork\n", get_time() - table->start_time, philo->id);

		printf("%lld %d is eating\n", get_time() - table->start_time, philo->id);
		usleep(table->time_to_eat * 1000);

		pthread_mutex_unlock(&table->forks[left_fork]);
		pthread_mutex_unlock(&table->forks[right_fork]);

		// 睡眠と思考
		printf("%lld %d is sleeping\n", get_time() - table->start_time, philo->id);
		usleep(table->time_to_sleep * 1000);
		printf("%lld %d is thinking\n", get_time() - table->start_time, philo->id);
	}
	return (NULL);
}
