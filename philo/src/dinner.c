/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:36:19 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/04/07 19:57:50 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	synchro_start(philo->table);
	while (!sim_finished(philo->table))
	{
		eat(philo);
		if (philo->full)
			break;
		print_status(philo, SLEEPING);
		good_usleep(philo->table->tts, philo->table);
	}
	return (NULL);
}

void	dinner(t_table *table)
{
	if (!table->n_eats)
		return ;
	// else if (table->n_philos == 1)
	// 	;
	create_or_join_all(table, CREATE);
	thread_control(&table->monitor, monitor, table, CREATE);
	table->start = time_control(MS);
	set_bool(&table->start_finish, &table->ready, true); // Simulation synchronized and ready to start
	create_or_join_all(table, JOIN);
}