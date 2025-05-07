/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:31:26 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:31:26 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	mutex_control(pthread_mutex_t *mutex, t_operations operation)
{
	int error;

	error = 0;
	if (operation == INIT)
		error = pthread_mutex_init(mutex, NULL);
	else if (operation == DESTROY)
		error = pthread_mutex_destroy(mutex);
	else if (operation == LOCK)
		error = pthread_mutex_lock(mutex);
	else if (operation == UNLOCK)
		error = pthread_mutex_unlock(mutex);
	if (error)
		err(RED "Error in mutex operations" RESET);
	return (error);
}

int	thread_control(pthread_t *thread, void *(*func)(void *), void *arg,
		t_operations operation)
{
	int error;

	error = 0;
	if (operation == CREATE)
		error = pthread_create(thread, NULL, func, arg);
	else if (operation == DETACH)
		error = pthread_detach(*thread);
	else if (operation == JOIN)
		error = pthread_join(*thread, NULL);
	if (error)
		err(RED "Error in thread operations" RESET);
	return (error);
}

long	time_control(t_time measure)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (measure == US)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else if (measure == MS)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (measure == S)
		return ((tv.tv_usec / 1e6) + tv.tv_sec);
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
