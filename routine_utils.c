#include "philosophers.h"

void    pick_fork(t_philo *data)
{
    if (data->ph_id % 2 == 0)
    {
        if (pthread_mutex_lock(&data->fork->fork_status) != 0)
            printf("philo %d picked up the left fork. (fork #%p)\n", data->ph_id, &data->fork->fork_status);
        if (pthread_mutex_lock(&data->fork->next->fork_status) != 0)
            printf("philo %d picked up the right fork. (fork #%p)\n", data->ph_id, &data->fork->next->fork_status);
    }
    else
    {
        if (pthread_mutex_lock(&data->fork->next->fork_status) != 0)
        {
            printf("philo %d picked up the left fork. (fork #%p)\n", data->ph_id, &data->fork->fork_status);
            if (pthread_mutex_lock(&data->fork->fork_status) != 0)
                printf("philo %d picked up the right fork. (fork #%p)\n", data->ph_id, &data->fork->next->fork_status);
        }
    }
    return ;
}

void    leave_fork(t_philo *data)
{
    if (data->ph_id % 2 == 0)
    {
        if (pthread_mutex_unlock(&data->fork->fork_status) != 0)
            printf("philo %d put down up the left fork. (fork #%p)\n", data->ph_id, &data->fork->fork_status);
        if (pthread_mutex_unlock(&data->fork->next->fork_status) != 0)
            printf("philo %d put down up the right fork. (fork #%p)\n", data->ph_id, &data->fork->next->fork_status);
    }
    else
    {
        if (pthread_mutex_unlock(&data->fork->next->fork_status))
        {
            printf("philo %d put down up the left fork. (fork #%p)\n", data->ph_id, &data->fork->fork_status);
            if (pthread_mutex_unlock(&data->fork->fork_status) != 0)
                printf("philo %d put down up the right fork. (fork #%p)\n", data->ph_id, &data->fork->next->fork_status);
        }
    }
    return ;
}