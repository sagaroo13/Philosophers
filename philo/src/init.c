/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:12:46 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/04/07 18:12:46 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void init_forks(t_table *table)
{
    int i;

    i = -1;
    table->forks = malloc_control(sizeof(t_fork) * table->n_philos);
    while (++i < table->n_philos)
    {
        mutex_control(&table->forks[i].fork, INIT);
        table->forks[i].id = i;
    }
}

static void assign_forks(t_philo *philo, t_fork *forks)
{
    philo->first = &forks[philo->id % philo->table->n_philos];
	philo->second = &forks[philo->id - 1];
	if (!(philo->id % 2))
	{
		philo->first = &forks[philo->id - 1];
		philo->second = &forks[philo->id % philo->table->n_philos];
	}
}

static void init_philos(t_table *table)
{
    int i;
    
    i = -1;
    table->philos = malloc_control(sizeof(t_philo) * table->n_philos);
    while (++i < table->n_philos)
    {
        table->philos[i].id = i + 1;
        table->philos[i].n_meals = 0;
        table->philos[i].full = false;
        table->philos[i].lst_meal_t = 0;
        table->philos[i].table = table;
        assign_forks(&table->philos[i], table->forks);
    }
}

void    init(t_table *table)
{
    table->end = false;
    init_forks(table);
    init_philos(table);
}