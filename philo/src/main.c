/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:30:57 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:30:57 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	print_philos_info(t_table *table)
// {
// 	for (int i = 0; i < table->n_philos; i++)
// 	{
// 		printf("Philo id: %d\nFirst fork: %d\nSecond fork: %d\n",
// 			table->philos[i].id, table->philos[i].first->id,
// 			table->philos[i].second->id);
// 		if (i < table->n_philos - 1)
// 			printf("\n");
// 	}
// }

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (err(CYAN "Usage: <n_philos> <time_to_die> <time_to_eat>"
				" <time_to_sleep> [<n_eats>]" RESET), EXIT_FAILURE);
	if (!parser(&table, argv))
		return (EXIT_FAILURE);
	if (!init(&table))
		return (clean_table(&table), EXIT_FAILURE);
	if (!dinner(&table))
		return (clean_table(&table), EXIT_FAILURE);
	clean_table(&table);
	return (EXIT_SUCCESS);
}
