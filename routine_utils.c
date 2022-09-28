#include "philosophers.h"

void    ending_c(t_ph *ph)
{
        if ((time_monitor(ph) - ph->last_meal) > ph->rules->t_death)
        {
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
}

void    ending_c_f(t_ph *ph)
{
        pthread_mutex_lock(&ph->rules->end_m);
        if ((time_monitor(ph) - ph->last_meal) > ph->rules->t_death)
            ph->rules->end = 1;
        if (ph->rules->end != 0 || ((time_monitor(ph) - ph->last_meal) > ph->rules->t_death))
        {
            unlock_f(ph);
            pthread_mutex_unlock(&ph->rules->end_m);
            pthread_exit(EXIT_SUCCESS);
        }
        pthread_mutex_unlock(&ph->rules->end_m);
}

void    lock_f(t_ph *ph)
{
    if (ph->ph_id % 2 != 0)
    {
        if (pthread_mutex_lock(&ph->fork->fork_m) == 0)
            (void)ph;
        if (pthread_mutex_lock(&ph->fork->next->fork_m) == 0)
            (void)ph;
    }
    else
    {
        if (pthread_mutex_lock(&ph->fork->next->fork_m) == 0)
        {
            if (pthread_mutex_lock(&ph->fork->fork_m) == 0)
                (void)ph;
        }
    }
    return ;
}

void    unlock_f(t_ph *ph)
{
    if (ph->ph_id % 2 != 0)
    {
        if (pthread_mutex_unlock(&ph->fork->fork_m) == 0)
            (void)ph;
        if (pthread_mutex_unlock(&ph->fork->next->fork_m) == 0)
            (void)ph;
    }
    else
    {
        if (pthread_mutex_unlock(&ph->fork->next->fork_m) == 0)
        {
            if (pthread_mutex_unlock(&ph->fork->fork_m) == 0)
                (void)ph;
        }
    }
    return ;
}

void    waiting(long int time, t_ph *ph)
{
    long int dest;

    dest = whattimeisit() + time;
    while (whattimeisit() < dest)
    {
        ending_c(ph);
        usleep(100);
    }
    return ;
}

void    sleep_time(t_ph *ph, long int time, int flag)
{
    long int    diff;

    diff = time_monitor(ph) - ph->last_meal;
    if (flag == 3)
        ending_c_f(ph);
    else
        ending_c(ph);
    if (flag == 2)
    {
        printf("%ld %d is thinking\n", time_monitor(ph), ph->ph_id);
        return ;
    }
    else if (flag == 3)
    {
        ph->last_meal = time_monitor(ph);
        printf("%ld %d is eating\n", time_monitor(ph), ph->ph_id);
        waiting(time, ph);
        ending_c_f(ph);
        return ;
    }
    else
    {
        if ((diff + time) >= ph->rules->t_death)
        {
            ending_c(ph);
            printf("%ld %d is sleeping\n", time_monitor(ph), ph->ph_id);
            waiting(ph->rules->t_death - (time_monitor(ph) - ph->last_meal), ph);
            pthread_mutex_lock(&ph->rules->end_m);
            ph->rules->end = 1;
            pthread_mutex_unlock(&ph->rules->end_m);
            pthread_exit(EXIT_SUCCESS);
        }
        else
        {
            printf("%ld %d is sleeping\n", time_monitor(ph), ph->ph_id);
            ending_c(ph);
            waiting(time, ph);
        }
    }
    return ;
}