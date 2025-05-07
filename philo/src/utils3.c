/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:31:43 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:31:43 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	err(const char *msg)
{
	printf("%s\n", msg);
}

void	clean_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		if (table->philos)
		{
			mutex_control(&table->philos[i].lst_meal_mtx, DESTROY);
			mutex_control(&table->philos[i].n_eats_mtx, DESTROY);
		}
		if (table->forks)
			mutex_control(&table->forks[i].fork, DESTROY);
	}
	mutex_control(&table->start_finish, DESTROY);
	mutex_control(&table->write, DESTROY);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
}

bool	create_or_join_all(t_table *table, t_operations operation)
{
	int	i;

	i = -1;
	if (operation == CREATE)
	{
		while (++i < table->n_philos)
		{
			if (thread_control(&table->philos[i].thread_id,
					simulation, &table->philos[i], operation))
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

bool	sim_finished(t_table *table)
{
	return (get_bool(&table->start_finish, &table->finish));
}
