#include "../include/philo.h"

bool sim_finished(t_table *table)
{
    return (get_bool(&table->start_finish, &table->finish));
}