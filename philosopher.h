/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:22:19 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/14 18:30:30 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_philo
{
	unsigned int 		id;
	unsigned int		philo_count;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		must_eat_count;
	unsigned int		someone_died;
	long				start_time;
	long 				last_meal_time;
    unsigned int 		fork_count;
	pthread_mutex_t 	*forks;
	int 				meals_eaten;
}t_philo;

typedef struct s_simulation
{
	t_philo *philos;
	pthread_t *threads;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
}t_simulation;


int is_digit(char c);
int ft_atoi(char *str);
long timestamp_ms(void);
void *philo_routine(void *arg);
int check_args(int argc, char **argv);
void init_rules(t_simulation *sim, char **argv);
void error_exit(char *msg);
void smart_sleep(int ms, t_philo *rules);
void *monitor_func(void *arg);
void init_philos_and_threads(t_simulation *sim);
void init_fork_mutex(t_simulation *sim);


#endif
