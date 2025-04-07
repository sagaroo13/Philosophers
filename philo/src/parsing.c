/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsagaro- <jsagaro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:12:54 by jsagaro-          #+#    #+#             */
/*   Updated: 2025/04/07 18:12:54 by jsagaro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static inline bool ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static long	ft_atol(const char *nptr)
{
	long            i;
	unsigned long res;

	i = 0;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
        err_exit(RED"Input must be positive"RESET);
	else if (nptr[i] == '+')
		i++;
    if (!ft_isdigit(nptr[i]))
        err_exit(RED"Input must be numeric"RESET);
    else
    {
	    while (ft_isdigit(nptr[i]))
		    res = (res * 10) + (nptr[i++] - '0');
    }
	return (res);
}

static long    check_input(const char* argvi)
{
    long n;
    
    n = ft_atol(argvi);
    if (n > INT_MAX)
        err_exit(RED"Input must fit in an int"RESET);
    return(n);
}

void    parser(t_table *table, char **argv)
{
    table->n_philos = check_input(argv[1]);
    table->ttd = check_input(argv[2]);
    table->tte = check_input(argv[3]);
    table->tts = check_input(argv[4]);
    if (argv[5])
        table->n_eats = check_input(argv[5]);
    else
        table->n_eats = -1;
}