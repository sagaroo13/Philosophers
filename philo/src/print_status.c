#include "../include/philo.h"

void	print_debug(t_philo *philo, t_status status, long elapsed)
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
		printf(GREEN"%-6ld 👤%02d is sleeping 😴[meals:%ld]\n"RESET,
			elapsed, philo->id, philo->n_meals);
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
	mutex_control(&philo->table->write, LOCK);
	if (DEBUG)
		print_debug(philo, status, elapsed);
	else
	{
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
	}
	mutex_control(&philo->table->write, UNLOCK);
}