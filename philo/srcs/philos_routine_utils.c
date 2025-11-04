/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:51:28 by shunwata          #+#    #+#             */
/*   Updated: 2025/11/04 15:53:50 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_table *table, t_philo *philo, int *left_fork, int *right_fork)
{
	*left_fork = philo->id - 1;
	*right_fork = philo->id % table->num_philos;
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
