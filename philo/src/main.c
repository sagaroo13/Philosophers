#include "../include/philo.h"

void print_philos_info(t_table *table)
{
    for (int i = 0; i < table->n_philos; i++)
    {
        printf("Philo id: %d\nFirst fork: %d\nSecond fork: %d\n", table->philos[i].id, table->philos[i].first->id, table->philos[i].second->id);
        if (i < table->n_philos - 1)
            printf("\n");
    }
}

int main(int argc, char **argv)
{
    t_table table;

    if (argc != 5 && argc != 6)
        err_exit(CYAN"Usage: <n_philos> <time_to_die> <time_to_eat>"
        " <time_to_sleep> [<n_eats>]"RESET);
    parser(&table, argv);
    init(&table);
    print_philos_info(&table);
    clean_table(&table);
    // printf("%ld\n", table.n_philos);
    // printf("%ld\n", table.ttd);
    // printf("%ld\n", table.tte);
    // printf("%ld\n", table.tts);
    // printf("%ld\n", table.n_eats);
}
