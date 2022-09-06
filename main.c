#include "philosophers.h"

// t_rules init_rules(char **av)
// {
//     t_rules rules;
//     rules.philo_id = ft_atoi(av[1]);
//     rules.t_death = ft_atoi(av[2]);
//     rules.t_eat = ft_atoi(av[3]);
//     rules.t_sleep = ft_atoi(av[4]);
//     if (av[5])
//         rules.meals_cap = ft_atoi(av[5]);
//     else
//         rules.meals_cap = 0;
//     return (rules);

// }

void    *philosopher(void *arg)
{
    t_list *fork;

    ft_print_nl("bonjour");
    fork = (t_list *)arg;
    pthread_mutex_lock(&(*fork).fork_status);
    pthread_mutex_unlock(&(*fork).fork_status);
    printf("\e[0;91mOn est dans le thread et on a rien a afficher\e[0m\n");
    pthread_exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    int nphilo;
    pthread_t **table;
    t_list *cutlery = NULL;
    t_list *fork;
    int i;
    int err;

    i = 0;
    err = 0;
    nphilo = ft_atoi(av[1]);
    table = malloc(sizeof(pthread_t *) * nphilo);
    while(i != nphilo)
    {
        table[i] = malloc(sizeof(pthread_t));
        fork = addback(&cutlery);
        printf("%p\n", fork);
        err = pthread_create(table[i], NULL, &philosopher, fork);
        i++;
    }
    while(i != nphilo)
    {
        pthread_join(*table[i], NULL);
        i++;
    }
    destroy_cutlery(cutlery);
    return (0);
}