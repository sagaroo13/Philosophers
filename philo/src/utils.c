/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:12:30 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/04/07 18:12:30 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	err_exit(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	clean_table(t_table *table)
{
	free(table->philos);
	free(table->forks);
}

void	*malloc_control(size_t q)
{
	void *result;

	result = malloc(q);
	if (!result)
		err_exit(RED "Malloc memory allocation failed" RESET);
	return (result);
}

void	mutex_control(pthread_mutex_t *mutex, t_operations operation)
{
	int err;

	err = 0;
	if (operation == INIT)
		err = pthread_mutex_init(mutex, NULL);
	else if (operation == DESTROY)
		err = pthread_mutex_destroy(mutex);
	else if (operation == LOCK)
		err = pthread_mutex_lock(mutex);
	else if (operation == UNLOCK)
		err = pthread_mutex_unlock(mutex);
	else
		err_exit(RED "Wrong mutex operation" RESET);
	if (err)
		err_exit(RED "Error in mutex operations" RESET);
}

void	thread_control(pthread_t *thread, void *(*func)(void *), void *arg,
		t_operations operation)
{
	int err;

	err = 0;
	if (operation == CREATE)
		err = pthread_create(thread, NULL, func, arg);
	else if (operation == DETACH)
		err = pthread_detach(*thread);
	else if (operation == JOIN)
		err = pthread_join(*thread, NULL);
	else
		err_exit(RED "Wrong thread operation" RESET);
	if (err)
		err_exit(RED "Error in thread operations" RESET);
}

time_t	current_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}