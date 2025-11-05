/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:32:36 by shunwata          #+#    #+#             */
/*   Updated: 2025/11/05 22:25:48 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

typedef struct s_mutex_combo
{
	pthread_mutex_t	mutex;
	bool			is_initialized;
}	t_mutex_combo;

typedef struct s_table
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_meals;
	long long		start_time;
	bool			simulation_should_end;
	t_philo			*philos;
	t_mutex_combo	*forks;
	t_mutex_combo	write_lock;
	t_mutex_combo	meal_lock;
	t_mutex_combo	death_lock;
	bool			alloc_failed;
}	t_table;

long long	get_time(void);
void		precise_sleep(long long target_time);
void		print_status(t_philo *philo, char *status);
void		cleanup(t_table *table);
int			ft_atoi(const char *str);

bool		init_table(t_table *table, char **argv);

bool		is_valid_args(int argc, char **argv);

void		*monitor_philos(t_table *table);

void		set_forks(t_table *table, t_philo *philo, int *left_fork, int *right_fork);
bool		get_forks(t_table *table, t_philo *philo, int fork1, int fork2);
void		return_forks(t_table *table, int fork1, int fork2);

void 		*philo_routine(void *arg);

#endif
