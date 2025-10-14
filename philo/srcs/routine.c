/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:09:14 by shunwata          #+#    #+#             */
/*   Updated: 2025/10/14 14:49:03 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lonely_philo(t_table *table, t_philo *philo, int left_fork)
{
	pthread_mutex_lock(&table->forks[left_fork].mutex);
	print_status(philo, "has taken a fork");
	precise_sleep(table->time_to_die + 1);
	pthread_mutex_unlock(&table->forks[left_fork].mutex);
	return (NULL);
}

void	get_forks(t_table *table, t_philo *philo, int fork1, int fork2)
{
	pthread_mutex_lock(&table->forks[fork1].mutex);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&table->forks[fork2].mutex);
	print_status(philo, "has taken a fork");
}

void	philo_eats(t_table *table, t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&table->meal_lock.mutex);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&table->meal_lock.mutex);
	precise_sleep(table->time_to_eat);
}

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
	// if (philo->id % 2 != 0) // (任意) スタートタイミングをずらす
	// 	usleep(100);
    while (!simulation_finished(table))
	{
		// 必要回数に達している場合は終了（フォーク取得前にチェック）
		if (table->num_meals > 0)
		{
			pthread_mutex_lock(&table->meal_lock.mutex);
			if (philo->eat_count >= table->num_meals)
			{
				pthread_mutex_unlock(&table->meal_lock.mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table->meal_lock.mutex);
		}
        if (table->num_philos == 1)
            return (lonely_philo(table, philo, left_fork));
        if (philo->id % 2 == 0)
            get_forks(table, philo, left_fork, right_fork);
        else
            get_forks(table, philo, right_fork, left_fork);
		philo_eats(table, philo);
		pthread_mutex_unlock(&table->forks[left_fork].mutex);
		pthread_mutex_unlock(&table->forks[right_fork].mutex);
		print_status(philo, "is sleeping");
		precise_sleep(table->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

bool simulation_finished(t_table *table)
{
	bool	is_finished;

	pthread_mutex_lock(&table->death_lock.mutex);
	is_finished = table->simulation_should_end;
	pthread_mutex_unlock(&table->death_lock.mutex);
	return (is_finished);
}
