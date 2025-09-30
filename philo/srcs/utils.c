/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:53:38 by shunwata          #+#    #+#             */
/*   Updated: 2025/09/08 17:54:21 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 現在時刻をミリ秒で取得する
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void precise_sleep(long long target_time)
{
	long long start;

	start = get_time();
	while ((get_time() - start) < target_time)
	{
		usleep(500); // 短いスリープを繰り返す
	}
}

void cleanup(t_table *table)
{
    for (int i = 0; i < table->num_philos; i++)
        pthread_mutex_destroy(&table->forks[i]);
    pthread_mutex_destroy(&table->write_lock);
    pthread_mutex_destroy(&table->meal_lock);
    pthread_mutex_destroy(&table->death_lock);
    free(table->forks);
    free(table->philos);
}

void print_status(t_philo *philo, char *status)
{
    long long current_time;

    pthread_mutex_lock(&philo->table->write_lock);
    // 誰かが死んでいたら、もう何も表示しない
    if (!simulation_finished(philo->table))
    {
        current_time = get_time() - philo->table->start_time;
        printf("%lld %d %s\n", current_time, philo->id, status);
    }
    pthread_mutex_unlock(&philo->table->write_lock);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}
