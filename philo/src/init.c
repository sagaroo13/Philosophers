/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:30:44 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:30:44 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	init_forks(t_table *table)
{
	int i;

	i = -1;
	table->forks = malloc(sizeof(t_fork) * table->n_philos);
	if (!table->forks)
		return (false);
	while (++i < table->n_philos)
	{
		if (mutex_control(&table->forks[i].fork, INIT))
			return (false);
		table->forks[i].id = i;
	}
	return (true);
}

static void	assign_forks(t_philo *philo, t_fork *forks)
{
	philo->first = &forks[philo->id % philo->table->n_philos];
	philo->second = &forks[philo->id - 1];
	if (!(philo->id % 2))
	{
		philo->first = &forks[philo->id - 1];
		philo->second = &forks[philo->id % philo->table->n_philos];
	}
}

static bool	init_philos(t_table *table)
{
	int i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philos)
		return (false);
	while (++i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].n_meals = 0;
		table->philos[i].full = false;
		table->philos[i].lst_meal_t = 0;
		table->philos[i].table = table;
		if (mutex_control(&table->philos[i].lst_meal_mtx, INIT))
			return (false);
		if (mutex_control(&table->philos[i].n_eats_mtx, INIT))
			return (false);
		assign_forks(&table->philos[i], table->forks);
	}
	return (true);
}

bool	init(t_table *table)
{
	table->finish = false;
	table->ready = false;
	table->ready_threads = 0;
	if (!init_forks(table) || !init_philos(table))
		return (false);
	if (mutex_control(&table->start_finish, INIT))
		return (false);
	if (mutex_control(&table->write, INIT))
		return (false);
	return (true);
}
