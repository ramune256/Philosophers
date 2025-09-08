/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:32:36 by shunwata          #+#    #+#             */
/*   Updated: 2025/09/08 18:48:53 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// 哲学者の状態を管理する構造体
typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

// プログラム全体の状態とルールを管理する構造体
typedef struct s_table
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_meals_required; // オプション引数
	long long		start_time;
	int				simulation_should_end;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock; // printfを保護するMutex
	pthread_mutex_t	meal_lock; // last_meal_timeやeat_countを保護するMutex
	pthread_mutex_t	death_lock; // 死亡フラグを保護するMutex
}	t_table;

/* --- 関数プロトタイプ --- */

// utils.c
long long	get_time(void);
int			ft_atoi(const char *str);
void 		*philo_routine(void *arg);

#endif
