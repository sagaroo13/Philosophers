/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:31:14 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:31:14 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_debug(t_philo *philo, t_status status, long elapsed)
{
	if (status == FORK_1 && !sim_finished(philo->table))
		printf(MAGENTA"%-6ld 👤%02d has taken fork nº1 🍴[meals:%ld][fork_id:%d]\n"RESET,
			elapsed, philo->id, philo->n_meals, philo->first->id);
	else if (status == FORK_2 && !sim_finished(philo->table))
		printf(MAGENTA"%-6ld 👤%02d has taken fork nº2 🍴[meals:%ld][fork_id:%d]\n"RESET,
			elapsed, philo->id, philo->n_meals, philo->second->id);
	else if (status == EATING && !sim_finished(philo->table))
		printf(CYAN"%-6ld 👤%02d is eating 🍝[meals:%ld]\n"RESET,
			elapsed, philo->id, philo->n_meals);
	else if (status == SLEEPING && !sim_finished(philo->table))
		printf(GREEN"%-6ld 👤%02d is sleeping 😴[meals:%ld][🕒:%ld]\n"RESET,
			elapsed, philo->id, philo->n_meals, philo->lst_meal_t);
	else if (status == THINKING && !sim_finished(philo->table))
		printf(YELLOW"%-6ld 👤%02d is thinking 💭[meals:%ld]\n"RESET,
			elapsed, philo->id, philo->n_meals);
	else if (status == DIED)
		printf(RED"%-6ld 👤%02d died 💀[meals:%ld]\n"RESET,
			elapsed, philo->id, philo->n_meals);
}


void	print_status(t_philo *philo, t_status status)
{
	long	elapsed;

	elapsed = time_control(MS) - philo->table->start;
	if (philo->full || sim_finished(philo->table))
		return ;
	mutex_control(&philo->table->write, LOCK);
	if (DEBUG)
		print_debug(philo, status, elapsed);
	else
	{
		if ((status == FORK_1 || status == FORK_2) && !sim_finished(philo->table))
			printf("%ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !sim_finished(philo->table))
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING && !sim_finished(philo->table))
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !sim_finished(philo->table))
			printf("%ld %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%ld %d died\n", elapsed, philo->id);
	}
	mutex_control(&philo->table->write, UNLOCK);
}