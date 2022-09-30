#include "philosophers.h"

void    list_init(t_ph *ph, t_list **list, int nph)
{
    int i;

    i = 0;
    while (i != nph)
    {
        (ph + i)->fork = addback(&(*list));
        i++;
    }
    return ;
}

int     meals_c(t_ph *ph)
{
    if (ph->meals == ph->rules->cap)
        {
            // printf("(%d): J'ai plus faim ! (%d repas)\n", ph->ph_id, meals);
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
        pthread_exit(EXIT_SUCCESS);
    if (ph->ph_id % 2 != 0)
        waiting(ph->rules->t_eat, ph);
    pthread_mutex_lock(&ph->rules->end_m);
    while (ph->rules->end == 0)
    {
        pthread_mutex_unlock(&ph->rules->end_m);
        ending_c(ph);
        // printf("bleh %d\n", ph->ph_id);
        lock_f(ph);
        // ending_c_f(ph);
        activity(ph, ph->rules->t_eat, 3);
        unlock_f(ph);
        activity(ph, ph->rules->t_sleep, 1);
        activity(ph, 0, 2);
        // printf("%d hasn't been eating for %ld msec.\n", ph->ph_id, (time_monitor(ph) - ph->last_meal));
        if ((time_monitor(ph) - ph->last_meal) > ph->rules->t_death)
        {
            // printf("(%d): Je suis mort de faim ! (pas mangé depuis %ldmsec)\n", ph->ph_id, (whattimeisit() - ph->last_meal));
            pthread_mutex_lock(&ph->rules->end_m);
            ph->rules->end = 1;
            pthread_mutex_unlock(&ph->rules->end_m);
            pthread_exit(EXIT_SUCCESS);
        }
        // printf("THINKING : MEALS CAP: %d : %d /%d\n", ph->ph_id, ph->meals, ph->rules->cap);
        ending_c(ph);
        // meals_c(ph);
        pthread_mutex_lock(&ph->rules->end_m);
    }
    pthread_mutex_unlock(&ph->rules->end_m);
    pthread_exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    int nph;
    pthread_t **threads;
    t_list *list = NULL;
    t_rules *rules = NULL;
    t_ph *ph = NULL;
    int i;
    int err;

    i = 0;
    if (ac == 0)
        return (0);
    err = 0;
    nph = ft_atoi(av[1]);
    threads = malloc(sizeof(pthread_t *) * nph);
    ph = malloc(sizeof(t_ph) * nph);
    rules = malloc(sizeof(t_rules));
    *rules = init_rules(av);
    rules->success = nph;
    list_init(ph, &list, nph);
    rules->start = whattimeisit();
    while(i != nph)
    {
        threads[i] = malloc(sizeof(pthread_t));
        (ph + i)->meals = 0;
        (ph + i)->ph_id = i + 1;
        (ph + i)->rules = rules;
        pthread_create(threads[i], NULL, philosopher, (ph + i));
        i++;
    }
    i = 0;
    while(i != nph)
    {
        err = pthread_join(*threads[i], NULL);
        if (err == 1)
            // printf("thread %d est mort.\n", (i + 1));
        // else
            printf("le thread %d n'a pas voulu mourir correctement. :'(", (i + 1));
        i++;
    }
    destroy_list(list);
    // dishcleaner(list);
    return (0);
}