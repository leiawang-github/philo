/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:22:19 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/25 11:50:43 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct s_simulation t_simulation;
typedef struct s_philo t_philo;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	long			last_meal_time;
	int				meals_eaten;
	t_simulation	*sim;
}	t_philo;

typedef struct s_simulation
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				someone_died;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t print_lock;
	pthread_t		monitor;
	t_philo			*philo;
}	t_simulation;

int is_digit(char c);
int ft_atoi(char *str);
long timestamp_ms(void);
void *philo_routine(void *arg);
int check_args(int argc, char **argv);
void init_sim(t_simulation *sim, char **argv);
void error_exit(char *msg);
void *monitor_func(void *arg);
void init_philo_and_thread(t_simulation *sim);
void cleanup_simulation(t_simulation *sim, int created_threads);
void init_fork_mutex(t_simulation *sim);
void smart_sleep(int ms, t_simulation *sim);
void safe_print(t_simulation *sim, const char *format, ...);

#endif
