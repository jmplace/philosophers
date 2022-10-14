#include "philosophers.h"

int     meals_c(t_ph *ph)
{
    if (ph->meals == ph->rules->cap)
        {
            // printf("(%d): J'ai plus faim ! (%d repas)\n", ph->ph_id, ph->meals);
            pthread_mutex_lock(&ph->rules->success_m);
            ph->rules->success--;
            // printf("success flag: %d\n", ph->rules->success);
            pthread_mutex_unlock(&ph->rules->success_m);
            return (1);
        }
    return (0);
}

void    *philosopher(void *arg)
{
    t_ph *ph;

    ph = (t_ph *)arg;
    ph->last_meal = 0;
    if (&(ph->fork->fork_m) == &(ph->fork->next->fork_m))
    {
        waiting(ph->rules->t_death, ph);
        printf("%ld %d died\n", time_monitor(ph), ph->ph_id);
        pthread_exit(EXIT_SUCCESS);
    }
    if (ph->ph_id % 2 != 0)
        waiting(ph->rules->t_eat, ph);
    pthread_mutex_lock(&ph->rules->end_m);
    while (ph->rules->end == 0)
    {
        pthread_mutex_unlock(&ph->rules->end_m);
        ending_c(ph, 0);
        lock_f(ph);
        // ending_c(ph, 1);
        a_eat(ph);
        unlock_f(ph);
        a_sleep(ph);
        a_think(ph);
        ending_c(ph, 0);
        pthread_mutex_lock(&ph->rules->end_m);
    }
    pthread_mutex_unlock(&ph->rules->end_m);
    pthread_exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    pthread_t **threads;
    t_list *list = NULL;
    t_rules *rules = NULL;
    t_ph *ph = NULL;
    int i;
    int err;

    i = -1;
    if (ac < 5 || ac > 6)
        return (0);
    err = 0;
    struct_init(&ph, &threads, &rules, av);
    ph_init(ph, &list, ft_atoi(av[1]), rules);
    while(++i != ft_atoi(av[1]))
        pthread_create(threads[i], NULL, philosopher, (ph + i));
    i = 0;
    while(i != ft_atoi(av[1]))
    {
        err = pthread_join(*threads[i], NULL);
        if (err == 1)
            printf("le thread %d n'a pas voulu mourir correctement. :'(", (i + 1));
        i++;
    }
    destroy_list(list);
    return (0);
}
