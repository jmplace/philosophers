#include "philosophers.h"

int    ending_c(t_ph *ph, int ulock_f)
{
        char buffer[200];
        if (success_c(ph, ulock_f) == 1)
            pthread_exit(EXIT_SUCCESS);
        if (((time_monitor(ph) - ph->last_meal) > ph->rules->t_death))
        {
//            printf("ending simulation here for %d: time: %ld, end flag: %d, success flag: %d with %d/%d meals.\n", ph->ph_id, (time_monitor(ph) - ph->last_meal), ph->rules->end, success_c(ph, 0), ph->meals, ph->rules->cap);
            report(time_monitor(ph), ph->ph_id, "ending simulation here");
            pthread_mutex_lock(&ph->rules->end_m);
            if (ph->rules->end != 3)
                ph->rules->end = 1;
            pthread_mutex_unlock(&ph->rules->end_m);
        }
        pthread_mutex_lock(&ph->rules->end_m);
        if (ph->rules->end != 0)
        {
            if (ulock_f == 1)
                unlock_f(ph);
            if (ph->rules->end == 1)
            {
                ph->rules->end = 3;
//                printf("%ld %d died\n", time_monitor(ph), ph->ph_id);
                report(time_monitor(ph), ph->ph_id, "died");
            }
            pthread_mutex_unlock(&ph->rules->end_m);
            pthread_exit(EXIT_SUCCESS);
        }
        pthread_mutex_unlock(&ph->rules->end_m);
        return 0;
}

void    lock_f(t_ph *ph)
{
    if (ph->ph_id % 2 != 0)
    {
        if (pthread_mutex_lock(&ph->fork->fork_m) == 0)
        {
//            printf("%ld %d PICKED HIS LEFT FORK\n", time_monitor(ph), ph->ph_id);
            pthread_mutex_lock(&ph->fork->next->fork_m);
//            printf("%ld %d PICKED HIS RIGHT FORK\n", time_monitor(ph), ph->ph_id);
        }
    }
    else
    {
        if (pthread_mutex_lock(&ph->fork->next->fork_m) == 0)
        {
//            printf("%ld %d PICKED HIS RIGHT FORK\n", time_monitor(ph), ph->ph_id);
            pthread_mutex_lock(&ph->fork->fork_m);
//            printf("%ld %d PICKED HIS LEFT FORK\n", time_monitor(ph), ph->ph_id);
        }
    }
    return ;
}

void    unlock_f(t_ph *ph)
{
    if (ph->ph_id % 2 != 0)
    {
        pthread_mutex_unlock(&ph->fork->fork_m);
        pthread_mutex_unlock(&ph->fork->next->fork_m);
    }
    else
    {
        pthread_mutex_unlock(&ph->fork->next->fork_m);
        pthread_mutex_unlock(&ph->fork->fork_m);
    }
    return ;
}

int     end_check(t_ph *ph)
{
    pthread_mutex_lock(&ph->rules->end_m);
    if (ph->rules->end != 0)
        return 1;
    else
        return 0;
    pthread_mutex_unlock(&ph->rules->end_m);
}

int     success_c(t_ph *ph, int ulock_f)
{
    pthread_mutex_lock(&ph->rules->success_m);
    if (ph->rules->success == 0)
    {
        pthread_mutex_unlock(&ph->rules->success_m);
        pthread_mutex_lock(&ph->rules->end_m);
        if (ulock_f == 1)
            unlock_f(ph);
        // printf("ending simulation here for %d: time: %ld, end flag: %d, success flag: %d with %d/%d meals.\n", ph->ph_id, (time_monitor(ph) - ph->last_meal), ph->rules->end, success_c(ph), ph->meals, ph->rules->cap);
        if (ph->rules->end != 3)
        {
            ph->rules->end = 3;
//            printf("%ld Everyone is full, now it's time to dance!\n", time_monitor(ph));
            report(time_monitor(ph), NO_PHILO, "%ld Everyone is full, now it's time to dance!\n");
        }
        pthread_mutex_unlock(&ph->rules->end_m);
        return (1);
    }
    pthread_mutex_unlock(&ph->rules->success_m);
    return (0);
}

int     a_sleep(t_ph *ph)
{
    int diff;

    diff = time_monitor(ph) - ph->last_meal;
    if (ending_c(ph, 0) == 0)
//        printf("%ld %d is sleeping\n", time_monitor(ph), ph->ph_id);
        report(time_monitor(ph), ph->ph_id, "is sleeping");
    if ((diff + ph->rules->t_sleep) >= ph->rules->t_death)
    {
        waiting(ph->rules->t_death - (time_monitor(ph) - ph->last_meal), ph);
        pthread_mutex_lock(&ph->rules->end_m);
        ph->rules->end = 1;
        pthread_mutex_unlock(&ph->rules->end_m);
    }
    else
        waiting(ph->rules->t_sleep, ph);
    return 0;
}

int     a_eat(t_ph *ph)
{
//        printf("%ld %d IS DOING ANOTHER CHECK BEFORE EATING. last meal = %ld, diff = %ld\n", time_monitor(ph), ph->ph_id, ph->last_meal, (time_monitor(ph) - ph->last_meal));
        // printf("MEALS CAP: %d : %d /%d\n", ph->ph_id, ph->meals, ph->rules->cap);
        ending_c(ph, 1);
        ph->last_meal = time_monitor(ph);
//        printf("%ld %d is eating\n", time_monitor(ph), ph->ph_id);
        report(time_monitor(ph), ph->ph_id, "is eating");
        ph->meals++;
        // printf("MEALS CAP: %d : %d /%d\n", ph->ph_id, ph->meals, ph->rules->cap);
        meals_c(ph);
        waiting_f(ph->rules->t_eat, ph);
        return 0;
}

int     a_think(t_ph *ph)
{
        if (ending_c(ph, 0) == 0)
//            printf("%ld %d is thinking\n", time_monitor(ph), ph->ph_id);
        report(time_monitor(ph), ph->ph_id, "is thinking");
        if (ph->rules->t_eat > ph->rules->t_sleep)
            waiting((ph->rules->t_eat - ph->rules->t_sleep), ph);
        return 0;
}