#include "../include/philo.h"

void    eat(t_philo *philo)
{
    mutex_control(&philo->first->fork, LOCK);
    print_status(philo, FORK_1);
    mutex_control(&philo->second->fork, LOCK);
    print_status(philo, FORK_2);
    set_long(&philo->lst_meal_mtx, &philo->lst_meal_t, time_control(MS));
    print_status(philo, EATING);
    good_usleep(philo->table->tte, philo->table);
    philo->n_meals++;
    if (philo->n_meals == philo->table->n_eats)
        set_bool(&philo->n_eats_mtx, &philo->full, true);
    mutex_control(&philo->first->fork, UNLOCK);
    mutex_control(&philo->second->fork, UNLOCK);
}