/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leia <leia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:22:19 by leiwang           #+#    #+#             */
/*   Updated: 2025/07/26 16:20:06 by leia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_simulation	t_simulation;
typedef struct s_philo		t_philo;

typedef struct s_philo
{
	unsigned int			id;
	pthread_t				thread;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			meal_lock;
	long					last_meal_time;
	int						meals_eaten;
	t_simulation			*sim;
}							t_philo;

typedef struct s_simulation
{
	int						philo_count;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	long					start_time;
	int						must_eat_count;
	int						someone_died;
	pthread_t				monitor;
	pthread_mutex_t			print_lock;
	pthread_mutex_t			death_lock;
	pthread_mutex_t			*forks;
	t_philo					*philo;
}							t_simulation;

// init_funcs
void						init_struct(t_simulation *sim, char **argv);
void						init_mutexes(t_simulation *sim);
void						init_sim(t_simulation *sim, char **argv);
void						init_philo(t_simulation *sim);

// fork_action_funcs
void						take_forks(t_philo *philo);
void						drop_forks(t_philo *philo);
void						philo_eat(t_philo *philo);
void						philo_think(t_philo *philo);
void						philo_sleep(t_philo *philo);

// utility funcs
int							is_digit(char c);
int							ft_atoi(char *str);

// monitor_funcs
int							check_death(t_simulation *sim, t_philo *philo);
void						*monitor_func(void *arg);

long						timestamp_ms(void);
void						*philo_routine(void *arg);
int							check_args(int argc, char **argv);
void						smart_sleep(long duration, t_simulation *sim);
void						safe_print(t_simulation *sim, const char *msg,
								int id);
void						start_threads(t_simulation *sim);
int							has_someone_died(t_simulation *sim);

// cleanup_funcs
void						error_exit(const char *msg);
void						destroy_forks(pthread_mutex_t *forks, int count);
void						destroy_forks_and_free(pthread_mutex_t *forks,
								int count);
void						destroy_and_exit(t_simulation *sim,
								pthread_mutex_t *forks, int count,
								const char *msg);
void						cleanup_simulation(t_simulation *sim,
								int fork_count);

#endif
