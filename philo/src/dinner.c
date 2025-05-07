/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:36:19 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:30:32 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    *monitor(void *arg)
{
    t_table	*table;

	table = (t_table *)arg;
	synchro_monitor_start(table);
	while (!table->finish)
	{
		died(table);
		good_usleep(1e3, table);
	}
	return (NULL);
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	synchro_thread_start(philo->table);
	set_long(&philo->lst_meal_mtx, &philo->lst_meal_t, time_control(MS));
	increase_long(&philo->table->start_finish, &philo->table->ready_threads);
	if (philo->id % 2) // Odd philos start thinking to desynchronize the simulation
		thinking(philo, false);
	while (!sim_finished(philo->table))
	{
		eating(philo);
		if (philo->full)
			break;
		sleeping(philo);
		thinking(philo, true);
	}
	return (NULL);
}

void	*alone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	synchro_thread_start(philo->table);
	set_long(&philo->lst_meal_mtx, &philo->lst_meal_t, time_control(MS));
	increase_long(&philo->table->start_finish, &philo->table->ready_threads);
	print_status(philo, FORK_1);
	while (!sim_finished(philo->table))
		usleep(100);
	return (NULL);
}

bool	dinner(t_table *table)
{
	if (!table->n_eats)
		return (true);
	else if (table->n_philos == 1)
	{
		if (thread_control(&table->philos[0].thread_id, alone_philo, &table->philos[0], CREATE))
			return (false);
	}
	else
	{
		if (!create_or_join_all(table, CREATE))
			return (false);
	}
	if (thread_control(&table->monitor, monitor, table, CREATE))
		return (false);
	table->start = time_control(MS);
	set_bool(&table->start_finish, &table->ready, true); // Simulation synchronized and ready to start
	create_or_join_all(table, JOIN);
	return (true);
}
