#include "philosophers.h"

int    ending_c(t_ph *ph)
{
        if (((time_monitor(ph) - ph->last_meal) > ph->rules->t_death) || success_c(ph) == 1)
        {
            printf("ending simulation here for %d: time: %ld, success flag: %d with %d/%d meals.\n", ph->ph_id, (time_monitor(ph) - ph->last_meal), success_c(ph), ph->meals, ph->rules->cap);
            pthread_mutex_lock(&ph->rules->end_m);
            ph->rules->end = 1;
            pthread_mutex_unlock(&ph->rules->end_m);
        }
        pthread_mutex_lock(&ph->rules->end_m);
        if (ph->rules->end != 0)
        {
            pthread_mutex_unlock(&ph->rules->end_m);
            pthread_exit(EXIT_SUCCESS);
        }
        pthread_mutex_unlock(&ph->rules->end_m);
        return 0;
}

int    ending_c_f(t_ph *ph)
{
        if (((time_monitor(ph) - ph->last_meal) > ph->rules->t_death) || success_c(ph) == 1)
        {
            printf("ending simulation here (_f ver) for %d: time: %ld, success flag: %d with %d/%d meals.\n", ph->ph_id, (time_monitor(ph) - ph->last_meal), success_c(ph), ph->meals, ph->rules->cap);
            pthread_mutex_lock(&ph->rules->end_m);
            ph->rules->end = 1;
            pthread_mutex_unlock(&ph->rules->end_m);
        }
        pthread_mutex_lock(&ph->rules->end_m);
        if (ph->rules->end != 0)
        {
            pthread_mutex_unlock(&ph->rules->end_m);
            unlock_f(ph);
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
            pthread_mutex_lock(&ph->fork->next->fork_m);
    }
    else
    {
        if (pthread_mutex_lock(&ph->fork->next->fork_m) == 0)
            pthread_mutex_lock(&ph->fork->fork_m);
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

int     success_c(t_ph *ph)
{
    pthread_mutex_lock(&ph->rules->success_m);
    if (ph->rules->success == 0)
    {
        pthread_mutex_unlock(&ph->rules->success_m);
        return (1);
    }
    pthread_mutex_unlock(&ph->rules->success_m);
    return (0);
}

void    activity(t_ph *ph, long int time, int flag)
{
    long int    diff;

    diff = time_monitor(ph) - ph->last_meal;
    // printf("passing through activity %d\n", ph->ph_id);
    if (flag == 3)
        ending_c_f(ph);
    else
        ending_c(ph);
    if (flag == 2)
    {
        ending_c(ph);
        printf("%ld %d is thinking\n", time_monitor(ph), ph->ph_id);
        return ;
    }
    else if (flag == 3)
    {
        // printf("MEALS CAP: %d : %d /%d\n", ph->ph_id, ph->meals, ph->rules->cap);
        ending_c_f(ph);
        ph->last_meal = time_monitor(ph);
        printf("%ld %d is eating\n", time_monitor(ph), ph->ph_id);
        ph->meals++;
        // printf("MEALS CAP: %d : %d /%d\n", ph->ph_id, ph->meals, ph->rules->cap);
        meals_c(ph);
        waiting_f(time, ph);
        return ;
    }
    else
    {
        if ((diff + time) >= ph->rules->t_death)
        {
            if (ending_c(ph) == 0)
                printf("%ld %d is sleeping\n", time_monitor(ph), ph->ph_id);
            waiting(ph->rules->t_death - (time_monitor(ph) - ph->last_meal), ph);
            pthread_mutex_lock(&ph->rules->end_m);
            ph->rules->end = 1;
            pthread_mutex_unlock(&ph->rules->end_m);
            pthread_exit(EXIT_SUCCESS);
        }
        else
        {
            if (ending_c(ph) == 0)
                printf("%ld %d is sleeping\n", time_monitor(ph), ph->ph_id);
            waiting(time, ph);
        }
    }
    return ;
}