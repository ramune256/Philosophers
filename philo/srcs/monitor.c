/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:19:56 by shunwata          #+#    #+#             */
/*   Updated: 2025/11/13 18:25:39 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	finish_eating(t_table *table)
{
	pthread_mutex_lock(&table->death_lock.mutex);
	table->simulation_should_end = true;
	pthread_mutex_unlock(&table->death_lock.mutex);
}

static void	someone_died(t_table *table, int i)
{
	pthread_mutex_unlock(&table->meal_lock.mutex);
	pthread_mutex_lock(&table->death_lock.mutex);
	table->simulation_should_end = true;
	pthread_mutex_lock(&table->write_lock.mutex);
	printf("%lld %d died\n", get_time() - table->start_time,
		table->philos[i].id);
	pthread_mutex_unlock(&table->write_lock.mutex);
	pthread_mutex_unlock(&table->death_lock.mutex);
}

void	*monitor_philos(t_table *table)
{
	int		i;
	bool	all_philos_have_eaten;

	while (1)
	{
		i = 0;
		all_philos_have_eaten = true;
		while (i < (table->num_philos))
		{
			pthread_mutex_lock(&table->meal_lock.mutex);
			if ((get_time() - table->philos[i].last_meal_time) > (table->time_to_die))
				return(someone_died(table, i), NULL);
			if (table->num_meals > 0 && (table->philos[i].eat_count) < (table->num_meals))
				all_philos_have_eaten = false;
			pthread_mutex_unlock(&table->meal_lock.mutex);
			i++;
		}
		if (table->num_meals > 0 && all_philos_have_eaten)
			return (finish_eating(table), NULL);
		usleep(100);
	}
	return (NULL);
}
