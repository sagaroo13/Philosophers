/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/04/07 19:58:21 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/04/07 19:58:21 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

long	time_control(t_time measure)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		err_exit("Gettimeofday failed");
	if (measure == US)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else if (measure == MS)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (measure == S)
		return ((tv.tv_usec / 1e6) + tv.tv_sec);
	else
		err_exit(RED "Wrong time operation" RESET);
	return (0);
}

void	good_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = time_control(US);
	while (time_control(US) - start < usec)
	{
		if (sim_finished(table))
			break ;
		elapsed = time_control(US) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (time_control(US) - start < usec)
				;
		}
	}
}
