#include "philosophers.h"

void    pick_fork(t_ph *data)
{
    if (data->ph_id % 2 != 0)
    {
        printf("%d is trying to pick up left fork.\n", data->ph_id);
        if (pthread_mutex_lock(&data->fork->fork_status) == 0)
            printf("philo %d picked up the left fork. (fork #%p)\n", data->ph_id, &data->fork->fork_status);
        else
            printf("warning: %d couldn't pick up the left fork.\n", data->ph_id);
        printf("%d is trying to pick up right fork.\n", data->ph_id);
        if (pthread_mutex_lock(&data->fork->next->fork_status) == 0)
            printf("philo %d picked up the right fork. (fork #%p)\n", data->ph_id, &data->fork->next->fork_status);
        else
            printf("warning: %d couldn't pick up right fork!\n", data->ph_id);
    }
    else
    {
        printf("%d is trying to pick up right fork.\n", data->ph_id);
        if (pthread_mutex_lock(&data->fork->next->fork_status) == 0)
        {
            printf("philo %d picked up the right fork. (fork #%p)\n", data->ph_id, &data->fork->fork_status);
            printf("%d is trying to pick up left fork.\n", data->ph_id);
            if (pthread_mutex_lock(&data->fork->fork_status) == 0)
                printf("philo %d picked up the left fork. (fork #%p)\n", data->ph_id, &data->fork->next->fork_status);
        }
        else
            printf("warning: %d couldn't pick up the right fork.\n", data->ph_id);
    }
    return ;
}

void    leave_fork(t_ph *data)
{
    if (data->ph_id % 2 != 0)
    {
        if (pthread_mutex_unlock(&data->fork->fork_status) == 0)
            printf("philo %d put down up the left fork. (fork #%p)\n", data->ph_id, &data->fork->fork_status);
        if (pthread_mutex_unlock(&data->fork->next->fork_status) == 0)
            printf("philo %d put down up the right fork. (fork #%p)\n", data->ph_id, &data->fork->next->fork_status);
    }
    else
    {
        if (pthread_mutex_unlock(&data->fork->next->fork_status) == 0)
        {
            printf("philo %d put down up the left fork. (fork #%p)\n", data->ph_id, &data->fork->fork_status);
            if (pthread_mutex_unlock(&data->fork->fork_status) == 0)
                printf("philo %d put down up the right fork. (fork #%p)\n", data->ph_id, &data->fork->next->fork_status);
        }
    }
    return ;
}

void    waiting(long int time)
{
    long int dest;

    dest = whattimeisit() + time;
    while (whattimeisit() < dest)
    {
        usleep(100);
    }
    return ;
}

void    sleep_time(t_ph *data, long int time, int flag)
{
    long int    diff;

    diff = whattimeisit() - data->last_meal;
    pthread_mutex_lock(&data->rules->end_m);
    if (data->rules->end == 0 && flag == 2)
    {
        printf("%ld: %d is thinking.\n", whattimeisit(), data->ph_id);
        pthread_mutex_unlock(&data->rules->end_m);
        return ;
    }
    else if (data->rules->end == 0 && flag == 3)
    {
        printf("%ld: %d is eating.\n", whattimeisit(), data->ph_id);
        pthread_mutex_unlock(&data->rules->end_m);
        waiting(time);
        return ;
    }
    else if (data->rules->end == 0)
    {
        if ((diff + time) >= data->rules->t_death)
        {
            if (flag == 1)
                printf("%ld: %d is sleeping.\n", whattimeisit(), data->ph_id);
            waiting((data->last_meal + data->rules->t_death) - whattimeisit());
            data->rules->end = 1;
        }
        else
        {
            printf("%ld: %d is sleeping.\n", whattimeisit(), data->ph_id);
            waiting(time);
        }
        pthread_mutex_unlock(&data->rules->end_m);
    }
    else
    {
        printf("(%d): Someone died: stopping the simulation.\n", data->ph_id);
        pthread_mutex_unlock(&data->rules->end_m);
        pthread_exit(EXIT_SUCCESS);
    }

    return ;
}