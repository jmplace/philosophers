#include "philosophers.h"

void    dataprinter(t_ph *data)
{
    printf("for i = %d, fork : %p\n", data->ph_id, (data->fork));
    printf("for i = %d, next fork : %p\n", data->ph_id, (data->fork->next));
    printf("ph_id : %p : %d\n", &(data->ph_id), data->ph_id);
    printf("t_death : %p : %ld\n", &(data->rules->t_death), data->rules->t_death);
    printf("t_eat : %p : %ld\n", &(data->rules->t_eat), data->rules->t_eat);
    printf("t_sleep : %p : %ld\n", &(data->rules->t_sleep), data->rules->t_sleep);
    printf("meals_cap : %p : %d\n", &(data->rules->meals_cap), data->rules->meals_cap);

    return ;
}

t_rules init_rules(char **av)
{
    t_rules rules;

    rules.end = 0;
    // rules.start = 0;
    // pthread_mutex_init(&rules.start_m, NULL);
    pthread_mutex_init(&(rules.end_m), NULL);
    rules.start = 0;
    rules.t_death = ft_atoi(av[2]);
    rules.t_eat = ft_atoi(av[3]);
    rules.t_sleep = ft_atoi(av[4]);
    if (av[5])
        rules.meals_cap = ft_atoi(av[5]);
    else
        rules.meals_cap = 0;
    return (rules);
}