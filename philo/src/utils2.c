/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:07:00 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:55:08 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *target, bool value)
{
	mutex_control(mutex, LOCK);
	*target = value;
	mutex_control(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *target)
{
	bool	value;

	mutex_control(mutex, LOCK);
	value = *target;
	mutex_control(mutex, UNLOCK);
	return (value);
}

void	set_long(pthread_mutex_t *mutex, long *target, long value)
{
	mutex_control(mutex, LOCK);
	*target = value;
	mutex_control(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *target)
{
	long	value;

	mutex_control(mutex, LOCK);
	value = *target;
	mutex_control(mutex, UNLOCK);
	return (value);
}

void	increase_long(pthread_mutex_t *mutex, long *target)
{
	mutex_control(mutex, LOCK);
	(*target)++;
	mutex_control(mutex, UNLOCK);
}
