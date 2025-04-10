/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/04/07 18:12:50 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/04/07 18:12:50 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_philos_info(t_table *table)
{
	for (int i = 0; i < table->n_philos; i++)
	{
		printf("Philo id: %d\nFirst fork: %d\nSecond fork: %d\n",
			table->philos[i].id, table->philos[i].first->id,
			table->philos[i].second->id);
		if (i < table->n_philos - 1)
			printf("\n");
	}
}

int	main(int argc, char **argv)
{
	t_table table;

	if (argc != 5 && argc != 6)
		err_exit(CYAN "Usage: <n_philos> <time_to_die> <time_to_eat>"
						" <time_to_sleep> [<n_eats>]" RESET);
	parser(&table, argv);
	init(&table);
	dinner(&table);
	// print_philos_info(&table);
	clean_table(&table);
}
