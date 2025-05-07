/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:31:19 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:31:19 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	synchro_thread_start(t_table *table)
{
	while (!get_bool(&table->start_finish, &table->ready))
		;
}

static bool	monitor_ready(t_table *table)
{
	bool	ready;

	ready = false;
	mutex_control(&table->start_finish, LOCK);
	if (table->ready_threads == table->n_philos)
		ready = true;
	mutex_control(&table->start_finish, UNLOCK);
	return (ready);
}

void	synchro_monitor_start(t_table *table)
{
	while (!monitor_ready(table))
		;
	good_usleep(1e2, table);
}
