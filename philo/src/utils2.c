/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:07:00 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/04/07 19:58:00 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	err(const char *msg)
{
	printf("%s\n", msg);
}

void	clean_table(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->n_philos)
	{
		mutex_control(&table->philos[i].lst_meal_mtx, DESTROY);
		mutex_control(&table->philos[i].n_eats_mtx, DESTROY);
		mutex_control(&table->forks[i].fork, DESTROY);
	}
	mutex_control(&table->start_finish, DESTROY);
	mutex_control(&table->write, DESTROY);
	free(table->philos);
	free(table->forks);
}

void	set_bool(pthread_mutex_t *mutex, bool *target, bool value)
{
	mutex_control(mutex, LOCK);
	*target = value;
	mutex_control(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *target)
{
	bool value;

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
	long value;

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

bool	create_or_join_all(t_table *table, t_operations operation)
{
	int	i;

	i = -1;
	if (operation == CREATE)
	{
		while (++i < table->n_philos)
		{
			if (thread_control(&table->philos[i].thread_id, simulation, &table->philos[i],
				operation))
				return (false);
		}
	}
	else if (operation == JOIN)
	{
		while (++i < table->n_philos)
			thread_control(&table->philos[i].thread_id, NULL, NULL, operation);
	}
	return (true);
}
