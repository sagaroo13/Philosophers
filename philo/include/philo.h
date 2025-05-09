/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:28:51 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:28:51 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/******************************************************************************
 *                                 Libraries								  *
 ******************************************************************************/

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/******************************************************************************
 *                                 Definitions								  *
 ******************************************************************************/
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

# define MAX_PHILOS 250
# define DEBUG 0

/******************************************************************************
 *                                 Structures								  *
 ******************************************************************************/

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			n_meals;
	bool			full;
	long			lst_meal_t;
	t_fork			*first;
	t_fork			*second;
	pthread_t		thread_id;
	pthread_mutex_t	lst_meal_mtx;
	pthread_mutex_t	n_eats_mtx;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long			n_philos;
	long			ttd;
	long			tte;
	long			tts;
	long			n_eats;
	long			start;
	long			ready_threads;
	bool			ready;
	bool			finish;
	pthread_mutex_t	start_finish;
	pthread_mutex_t	write;
	pthread_t		monitor;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;

typedef enum e_operations
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	DETACH,
	JOIN,
}	t_operations;

typedef enum e_time
{
	US,
	MS,
	S,
}	t_time;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FORK_1,
	FORK_2,
}	t_status;

/******************************************************************************
 *                                 Prototypes								  *
 ******************************************************************************/

void	err(const char *msg);
int		mutex_control(pthread_mutex_t *mutex, t_operations operation);
int		thread_control(pthread_t *thread, void *(*func)(void *), void *arg,
			t_operations operation);
long	time_control(t_time measure);
bool	parser(t_table *table, char **argv);
bool	init(t_table *table);
void	clean_table(t_table *table);
void	set_bool(pthread_mutex_t *mutex, bool *target, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *target);
void	set_long(pthread_mutex_t *mutex, long *target, long value);
long	get_long(pthread_mutex_t *mutex, long *target);
void	increase_long(pthread_mutex_t *mutex, long *target);
bool	dinner(t_table *table);
void	*monitor(void *arg);
void	synchro_thread_start(t_table *table);
void	*simulation(void *arg);
bool	create_or_join_all(t_table *table, t_operations operation);
bool	sim_finished(t_table *table);
void	print_status(t_philo *philo, t_status status);
void	good_usleep(long usec, t_table *table);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo, bool print);
void	died(t_table *table);
void	synchro_monitor_start(t_table *table);

#endif