#include "../include/philo.h"

void	print_status(t_philo *philo, t_status status)
{
	long	elapsed;

	elapsed = time_control(MS) - philo->table->start;
	mutex_control(&philo->table->write, LOCK);
	if ((status == FORK_1 || status == FORK_2) && !sim_finished(philo->table))
		printf(MAGENTA"%-6ld %d has taken a fork\n"RESET, elapsed, philo->id);
	else if (status == EATING && !sim_finished(philo->table))
		printf(CYAN"%-6ld %d is eating\n"RESET, elapsed, philo->id);
	else if (status == SLEEPING && !sim_finished(philo->table))
		printf(GREEN"%-6ld %d is sleeping\n"RESET, elapsed, philo->id);
	else if (status == THINKING && !sim_finished(philo->table))
		printf(YELLOW"%-6ld %d is thinking\n"RESET, elapsed, philo->id);
	else if (status == DIED)
		printf(RED"%-6ld %d died\n"RESET, elapsed, philo->id);
	mutex_control(&philo->table->write, UNLOCK);
}