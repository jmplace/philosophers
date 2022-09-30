#include "philosophers.h"

void    dataprinter(t_ph *data)
{
    printf("for i = %d, fork : %p\n", data->ph_id, (data->fork));
    printf("for i = %d, next fork : %p\n", data->ph_id, (data->fork->next));
    printf("ph_id : %p : %d\n", &(data->ph_id), data->ph_id);
    printf("t_death : %p : %ld\n", &(data->rules->t_death), data->rules->t_death);
    printf("t_eat : %p : %ld\n", &(data->rules->t_eat), data->rules->t_eat);
    printf("t_sleep : %p : %ld\n", &(data->rules->t_sleep), data->rules->t_sleep);
    printf("cap : %p : %d\n", &(data->rules->cap), data->rules->cap);

    return ;
}