#include "../include/philo.h"

void    *monitor(void *arg)
{
    t_table	*table;

	table = (t_table *)arg;
	synchro_start(table);
	return (NULL);
}