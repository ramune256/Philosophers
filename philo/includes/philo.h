/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:32:36 by shunwata          #+#    #+#             */
/*   Updated: 2025/10/01 20:05:55 by shunwata         ###   ########.fr       */
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
	int				num_meals_required;
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
int			ft_atoi(const char *str);
void		precise_sleep(long long target_time);
void		cleanup(t_table *table);
void		print_status(t_philo *philo, char *status);
int			init_table(t_table *table, char **argv);
void 		*philo_routine(void *arg);
bool		simulation_finished(t_table *table);

#endif
