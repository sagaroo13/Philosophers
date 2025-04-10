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

void	thinking(t_philo *philo)
{
	long	ttt;
	long	elapsed;

	elapsed = (time_control(MS) - philo->lst_meal_t) * 1e3;
	ttt = (philo->table->ttd - elapsed) / 2;
	// printf(RED"%f\t%f\n"RESET, (ttt / 1e3), (elapsed /1e3));
	print_status(philo, THINKING);
	if (ttt > 0)
		good_usleep(ttt, philo->table);
}

void	died(t_table *table)
{
	int	i;
	long	elapsed;
	// long	lst_meal_t;

	i = -1;
	while (++i < table->n_philos)
	{
		// get_long(&table->philos[i].lst_meal_mtx, &lst_meal_t);
		elapsed = (time_control(MS) - table->philos[i].lst_meal_t) * 1e3;
		// printf("%ld\t%ld\n", elapsed, table->ttd);
		if (elapsed >= table->ttd)
		{
			print_status(&table->philos[i], DIED);
			set_bool(&table->start_finish, &table->finish, true);
			break ;
		}
	}
}