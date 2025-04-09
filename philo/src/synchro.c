#include "../include/philo.h"

void	synchro_start(t_table *table)
{
	while (!get_bool(&table->start_finish, &table->ready))
		;
}