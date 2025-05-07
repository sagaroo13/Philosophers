/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:31:07 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/05/07 11:31:07 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static long	ft_atol(const char *nptr)
{
	long			i;
	unsigned long	res;

	i = 0;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		return (err(RED "Input must be positive" RESET), -1);
	else if (nptr[i] == '+')
		i++;
	if (!ft_isdigit(nptr[i]))
		return (err(RED "Input must be numeric" RESET), -1);
	else
	{
		while (ft_isdigit(nptr[i]))
			res = (res * 10) + (nptr[i++] - '0');
	}
	return (res);
}

static long	check_input(const char *argvi)
{
	long	n;

	n = ft_atol(argvi);
	if (n == -1)
		return (n);
	else if (n > INT_MAX)
		return (err(RED "Input must fit in an int" RESET), -1);
	return (n);
}

bool	parser(t_table *table, char **argv)
{
	table->n_philos = check_input(argv[1]);
	if (table->n_philos == -1)
		return (false);
	else if (table->n_philos > MAX_PHILOS)
		return (err(RED"Philos must be less than 250"RESET), false);
	table->ttd = check_input(argv[2]) * 1e3;
	table->tte = check_input(argv[3]) * 1e3;
	table->tts = check_input(argv[4]) * 1e3;
	if (table->ttd == -1 * 1e3 || table->tte == -1 * 1e3
		|| table->tts == -1 * 1e3)
		return (false);
	if (argv[5])
	{
		table->n_eats = check_input(argv[5]);
		if (table->n_eats == -1)
			return (false);
	}
	else
		table->n_eats = -1;
	return (true);
}
