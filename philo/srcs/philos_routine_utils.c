/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:51:28 by shunwata          #+#    #+#             */
/*   Updated: 2025/11/27 19:04:26 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_table *table, t_philo *philo, int *l_fork, int *r_fork)
{
	*l_fork = philo->id - 1;
	*r_fork = philo->id % table->num_philos;
}

bool	get_forks(t_table *table, t_philo *philo, int fork1, int fork2)
{
	pthread_mutex_lock(&table->forks[fork1].mutex);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&table->forks[fork2].mutex);
	print_status(philo, "has taken a fork");
	return (true);
}

void	return_forks(t_table *table, int fork1, int fork2)
{
	pthread_mutex_unlock(&table->forks[fork1].mutex);
	pthread_mutex_unlock(&table->forks[fork2].mutex);
}

bool	simulation_finished(t_table *table)
{
	bool	is_finished;

	pthread_mutex_lock(&table->death_lock.mutex);
	is_finished = table->simulation_should_end;
	pthread_mutex_unlock(&table->death_lock.mutex);
	return (is_finished);
}
