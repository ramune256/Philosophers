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
	// if (philo->id % 2 != 0)
	// 	usleep(100);

	while (!simulation_finished(table))
	{
		// 食事アクション
		if (philo->id % 2 == 0)
		{
			// 偶数IDの哲学者：左 → 右 の順で取る
			pthread_mutex_lock(&table->forks[left_fork]);
			// printf("%lld %d has taken a fork\n", get_time() - table->start_time, philo->id);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(&table->forks[right_fork]);
			// printf("%lld %d has taken a fork\n", get_time() - table->start_time, philo->id);
			print_status(philo, "has taken a fork");
		}
		else
		{
			// 奇数IDの哲学者：右 → 左 の順で取る
			pthread_mutex_lock(&table->forks[right_fork]);
			// printf("%lld %d has taken a fork\n", get_time() - table->start_time, philo->id);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(&table->forks[left_fork]);
			// printf("%lld %d has taken a fork\n", get_time() - table->start_time, philo->id);
			print_status(philo, "has taken a fork");
		}

		// printf("%lld %d is eating\n", get_time() - table->start_time, philo->id);
		print_status(philo, "is eating");
		// 食事開始時刻を記録
        pthread_mutex_lock(&table->meal_lock);
		philo->last_meal_time = get_time();
        philo->eat_count++;
        pthread_mutex_unlock(&table->meal_lock);

		// usleep(table->time_to_eat * 1000);
		precise_sleep(table->time_to_eat);

		pthread_mutex_unlock(&table->forks[left_fork]);
		pthread_mutex_unlock(&table->forks[right_fork]);

		// 睡眠と思考アクション
		// printf("%lld %d is sleeping\n", get_time() - table->start_time, philo->id);
		print_status(philo, "is sleeping");
		// usleep(table->time_to_sleep * 1000);
		precise_sleep(table->time_to_sleep);
		// printf("%lld %d is thinking\n", get_time() - table->start_time, philo->id);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

bool simulation_finished(t_table *table)
{
	bool	is_finished;

	pthread_mutex_lock(&table->death_lock);
	is_finished = table->simulation_should_end;
	pthread_mutex_unlock(&table->death_lock);
	return (is_finished);
}
