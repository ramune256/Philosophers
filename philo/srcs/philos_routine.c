/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:09:14 by shunwata          #+#    #+#             */
/*   Updated: 2025/11/27 18:57:58 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*lonely_philo(t_table *table, t_philo *philo, int left_fork)
{
	pthread_mutex_lock(&table->forks[left_fork].mutex);
	print_status(philo, "has taken a fork");
	precise_sleep(table->time_to_die + 1);
	pthread_mutex_unlock(&table->forks[left_fork].mutex);
	return (NULL);
}

static void	philo_eats(t_table *table, t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&table->meal_lock.mutex);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&table->meal_lock.mutex);
	precise_sleep(table->time_to_eat);
}

static bool	no_need_to_eat(t_table *table, t_philo *philo)
{
	if (table->num_meals > 0)
	{
		if ((philo->eat_count) >= (table->num_meals))
			return (true);
	}
	return (false);
}

static bool	simulation_finished(t_table *table)
{
	bool	is_finished;

	pthread_mutex_lock(&table->death_lock.mutex);
	is_finished = table->simulation_should_end;
	pthread_mutex_unlock(&table->death_lock.mutex);
	return (is_finished);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	int		left_fork;
	int		right_fork;

	philo = (t_philo *)arg;
	table = philo->table;
	set_forks(table, philo, &left_fork, &right_fork);
	if (table->num_philos == 1)
		return (lonely_philo(table, philo, left_fork));
	(void)((philo->id % 2 == 0) && usleep(1000));
	while (!simulation_finished(table))
	{
		if (no_need_to_eat(table, philo))
			return (NULL);
		(void)((philo->id % 2 == 0 && get_forks(table, philo, left_fork,
			right_fork)) || get_forks(table, philo, right_fork, left_fork));
		if (simulation_finished(table))
			return (return_forks(table, left_fork, right_fork), NULL);
		philo_eats(table, philo);
		return_forks(table, left_fork, right_fork);
		(print_status(philo, "is sleeping"), precise_sleep(table->time_to_sleep));
		(print_status(philo, "is thinking"), usleep(500));
	}
	return (NULL);
}
