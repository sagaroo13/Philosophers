/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:13:06 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/04/07 18:13:06 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/******************************************************************************
*                                 Libraries                                   *
******************************************************************************/

#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

/******************************************************************************
*                                 Definitions                                 *
******************************************************************************/
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define RESET   "\033[0m"

/******************************************************************************
*                                 Structures                                  *
******************************************************************************/

typedef struct s_table t_table;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int id;
}   t_fork;

typedef struct s_philo
{
    int id;
    long n_meals;
    bool full;
    long lst_meal_t;
    t_fork *first;
    t_fork *second;
    pthread_t thread_id;
    t_table *table;
}   t_philo;

typedef struct s_table
{
    long n_philos;
    long ttd;
    long tte;
    long tts;
    long n_eats;
    long start;
    bool end;
    t_fork *forks;
    t_philo *philos;
} t_table;

typedef enum e_operations
{
    INIT,
    DESTROY,
    LOCK,
    UNLOCK,
    CREATE,
    DETACH,
    JOIN,
} t_operations;

/******************************************************************************
*                                 Prototypes                                  *
******************************************************************************/

void    err_exit(const char *msg);
void    *malloc_control(size_t q);
void    mutex_control(pthread_mutex_t *mutex, t_operations operation);
void    thread_control(pthread_t *thread, void *(*func)(void *), void *arg, t_operations operation);
void    parser(t_table *table, char **argv);
void    init(t_table *table);
void    clean_table(t_table *table);

#endif