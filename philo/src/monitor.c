#include "../include/philo.h"

void    *monitor(void *arg)
{
    t_table	*table;

	table = (t_table *)arg;
	synchro_start(table);
	printf(BLUE"%ld\n"RESET, time_control(US));
	while (!table->finish)
	{
		died(table);
		good_usleep(1e3, table);
	}
	return (NULL);
}