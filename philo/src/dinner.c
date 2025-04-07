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

void	simulation(t_table *table)
{
}

void	dinner(t_table *table)
{
	int i;

	i = -1;
	if (!table->n_eats)
		return ;
	else if (table->n_philos == 1)
		;
	else
	{
		while (++i < table->n_philos)
			thread_control(&table->philos[i].id, simulation, &table->philos[i],
				CREATE);
	}
}