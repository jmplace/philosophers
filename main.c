#include "philosophers.h"

t_rules init_rules(char **av)
{
    t_rules rules;

    // rules = (t_rules)malloc(sizeof(t_rules));
    // ft_print_nl("inside init_rules");
    rules.fork = NULL;
    rules.t_death = 0;
    rules.t_death = ft_atoi(av[2]);
    // ft_print_nl("after t_death init");
    // printf("t_death = %d\n", rules.t_death);
    rules.t_eat = ft_atoi(av[3]);
    // ft_print_nl("after t_eat init");
    rules.t_sleep = ft_atoi(av[4]);
    if (av[5])
        rules.meals_cap = ft_atoi(av[5]);
    else
        rules.meals_cap = 0;
    return (rules);
}

void    *philosopher(void *arg)
{
    t_list *fork;
    t_rules *rules;
    struct timeval now;
    struct timeval last_meal;

    rules = (t_rules *)arg;
    // rules->last_meal = gettimeofday(tv_usec, NULL);
    gettimeofday(&now, NULL);
    gettimeofday(&last_meal, NULL);
    printf("\e[0;91mOn est dans le thread et on veut la valeur de now: %ld\e[0m\n", now.tv_usec);
    while ((now.tv_usec - last_meal.tv_usec) < 100)
    {
        gettimeofday(&now, NULL);
        printf("now: %ld\n", now.tv_usec);
        printf("un tour a été fait ! la diff est de: %ld\n", (now.tv_usec - last_meal.tv_usec));
    }
    printf("Le philosophe est mort. Long live the philosopher !\n");
    // sleep(5);

    // while (((t_rules *)arg->last_meal - now) < (t_rules *)arg->t_death) 
    // {
    //      now = gettimeofday(tv_usec, NULL);
    //      fork = (t_rules *)arg->fork;
    //      pthread_mutex_lock(&(*seating).fork_status);
    //      pthread_mutex_unlock(&(*seating).fork_status);
    // }
    // gettimeofday(&now, NULL);
    // printf("\e[0;91mOn est dans le thread et on veut la valeur de now: %ld\e[0m\n", now.tv_usec);
    pthread_exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    int nphilo;
    pthread_t **table;
    t_list *cutlery = NULL;
    t_rules rules;
    t_list *fork;
    int i;
    int err;

    i = 0;
    err = 0;
    nphilo = ft_atoi(av[1]);
    table = malloc(sizeof(pthread_t *) * nphilo);
    // ft_print_nl("avant init rules");
    // rules = malloc(sizeof(t_rules));
    rules = init_rules(av);
    // ft_print_nl("après init rules");
    while(i != nphilo)
    {
        table[i] = malloc(sizeof(pthread_t));
        rules.fork = addback(&cutlery);
        printf("%p\n", fork);
        err = pthread_create(table[i], NULL, &philosopher, &rules);
        printf("err = %d\n", err);
        i++;
    }
    i = 0;
    while(i != nphilo)
    {
        pthread_join(*table[i], NULL);
        i++;
    }
    destroy_cutlery(cutlery);
    return (0);
}