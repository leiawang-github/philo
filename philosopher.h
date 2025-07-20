/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:22:19 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/20 21:17:52 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_simulation t_simulation;
typedef struct s_philo t_philo;

typedef struct s_philo
{
	unsigned int	id;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*forks;
	int				fork_count;
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
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	t_philo			*philos;
}	t_simulation;

int is_digit(char c);
int ft_atoi(char *str);
long timestamp_ms(void);
void *philo_routine(void *arg);
int check_args(int argc, char **argv);
void init_rules(t_simulation *sim, char **argv);
void error_exit(char *msg);
void *monitor_func(void *arg);
void init_philos_and_threads(t_simulation *sim);
void init_fork_mutex(t_simulation *sim);
void smart_sleep(int ms, t_simulation *sim);

#endif
