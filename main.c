#include "philosophers.h"

void    dataprinter(t_philo *data)
{
    printf("for i = %d, fork : %p\n", data->ph_id, (data->fork));
    printf("for i = %d, next fork : %p\n", data->ph_id, (data->fork->next));
    printf("ph_id : %p : %d\n", &(data->ph_id), data->ph_id);
    printf("t_death : %p : %d\n", &(data->rules->t_death), data->rules->t_death);
    printf("t_eat : %p : %d\n", &(data->rules->t_eat), data->rules->t_eat);
    printf("t_sleep : %p : %d\n", &(data->rules->t_sleep), data->rules->t_sleep);
    printf("meals_cap : %p : %d\n", &(data->rules->meals_cap), data->rules->meals_cap);

    return ;
}

t_rules init_rules(char **av)
{
    t_rules rules;

    rules.t_death = 0;
    rules.t_death = ft_atoi(av[2]);
    rules.t_eat = ft_atoi(av[3]);
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
    t_philo *data;
    struct timeval now;
    struct timeval last_meal;
    int meals;

    data = (t_philo *)arg;
    fork = data->fork;
    meals = 0;
    gettimeofday(&now, NULL);
    last_meal = now;
    // pthread_mutex_lock(&(*fork).fork_status);
    // dataprinter(data);
    while ((now.tv_usec - last_meal.tv_usec) < 500)
    {
        if (pthread_mutex_lock(&(*fork).fork_status) == 0)
        {
            gettimeofday(&last_meal, NULL);
            if (data->rules->meals_cap != 0)
            {
                meals++;
                printf("Philosopher %d: meal %d/%d\n", data->ph_id, meals, data->rules->meals_cap);
                if (meals == data->rules->meals_cap)
                    break;
            }
            printf("%ld: Philosopher %d is eating.\n", last_meal.tv_usec, data->ph_id);
            usleep(data->rules->t_eat);
            pthread_mutex_unlock(&(*fork).fork_status);
        }
        gettimeofday(&now, NULL);
        // printf("%ld: Philosopher %d is sleeping.\n", now.tv_usec, data->ph_id);
        usleep(data->rules->t_sleep);
        gettimeofday(&now, NULL);
        // printf("%ld: Philosopher %d is thinking.\n", now.tv_usec, data->ph_id);
        gettimeofday(&now, NULL);
    }
    gettimeofday(&now, NULL);
    printf("\e[1;91m%ld: Philosopher %d is dead. Long live the philosopher !\nhe made it to %d meals eaten out of %d.\n\e[22;91m\n", now.tv_usec, data->ph_id, meals, data->rules->meals_cap);
    // pthread_mutex_unlock(&(*fork).fork_status);
    pthread_exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    int nphilo;
    pthread_t **table;
    t_list *cutlery = NULL;
    t_rules *rules = NULL;
    t_philo *philo = NULL;
    int i;
    int err;

    i = 0;
    if (ac == 0)
        return (0);
    err = 0;
    nphilo = ft_atoi(av[1]);
    table = malloc(sizeof(pthread_t *) * nphilo);
    philo = malloc(sizeof(t_philo) * nphilo);
    rules = malloc(sizeof(t_rules));
    *rules = init_rules(av);
    while(i != nphilo)
    {
        table[i] = malloc(sizeof(pthread_t));
        (philo + i)->fork = addback(&cutlery);
        (philo + i)->ph_id = i + 1;
        (philo + i)->rules = rules;
        pthread_create(table[i], NULL, philosopher, (philo + i));
        i++;
    }
    i = 0;
    // listprinter(cutlery);
    while(i != nphilo)
    {
        err = pthread_join(*table[i], NULL);
        if (err == 0)
            printf("thread %d est mort.\n", (i + 1));
        else
            printf("le thread %d n'a pas voulu mourir correctement. :'(", (i + 1));
        i++;
    }
    destroy_cutlery(cutlery);
    return (0);
}


/*
    avant de usleep, verifier si le philo meurt pendant ce laps de temps !
*/