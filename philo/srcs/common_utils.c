/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:53:38 by shunwata          #+#    #+#             */
/*   Updated: 2025/11/13 18:29:37 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long long target_time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < target_time)
		usleep(500);
}

void	print_status(t_philo *philo, char *status)
{
	long long	current_time;

	pthread_mutex_lock(&philo->table->death_lock.mutex);
	if (!philo->table->simulation_should_end)
	{
		pthread_mutex_lock(&philo->table->write_lock.mutex);
		current_time = get_time() - philo->table->start_time;
		printf("%lld %d %s\n", current_time, philo->id, status);
		pthread_mutex_unlock(&philo->table->write_lock.mutex);
	}
	pthread_mutex_unlock(&philo->table->death_lock.mutex);
}

void cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if ((table->forks) && (table->forks[i].is_initialized))
			pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
	if (table->write_lock.is_initialized)
		pthread_mutex_destroy(&table->write_lock.mutex);
	if (table->meal_lock.is_initialized)
		pthread_mutex_destroy(&table->meal_lock.mutex);
	if (table->death_lock.is_initialized)
		pthread_mutex_destroy(&table->death_lock.mutex);
	free(table->forks);
	free(table->philos);
}
