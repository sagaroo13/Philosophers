/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:30:20 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:30:20 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo)
{
	mutex_control(&philo->first->fork, LOCK);
	print_status(philo, FORK_1);
	mutex_control(&philo->second->fork, LOCK);
	print_status(philo, FORK_2);
	set_long(&philo->lst_meal_mtx, &philo->lst_meal_t, time_control(MS));
	philo->n_meals++;
	print_status(philo, EATING);
	good_usleep(philo->table->tte, philo->table);
	if (philo->n_meals == philo->table->n_eats)
		set_bool(&philo->n_eats_mtx, &philo->full, true);
	mutex_control(&philo->first->fork, UNLOCK);
	mutex_control(&philo->second->fork, UNLOCK);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	good_usleep(philo->table->tts, philo->table);
}

void	thinking(t_philo *philo, bool print)
{
	long	ttt;
	long	elapsed;

	elapsed = (time_control(MS) - philo->lst_meal_t) * 1e3;
	ttt = (philo->table->ttd - elapsed - philo->table->tte) / 2;
	if (ttt <= 0)
		ttt = 1 * 1e3;
	else if (ttt > 700 * 1e3)
		ttt = 300 * 1e3;
	if (print)
		print_status(philo, THINKING);
	good_usleep(ttt, philo->table);
}

void	died(t_table *table)
{
	int	i;
	long	elapsed;

	i = -1;
	while (++i < table->n_philos)
	{
		if (get_bool(&table->philos[i].n_eats_mtx, &table->philos[i].full))
			continue;
		mutex_control(&table->philos[i].lst_meal_mtx, LOCK);
		elapsed = (time_control(MS) - table->philos[i].lst_meal_t) * 1e3;
		if (elapsed >= table->ttd)
		{
			print_status(&table->philos[i], DIED);
			set_bool(&table->start_finish, &table->finish, true);
			mutex_control(&table->philos[i].lst_meal_mtx, UNLOCK);
			return ;
		}
		mutex_control(&table->philos[i].lst_meal_mtx, UNLOCK);
	}
}
