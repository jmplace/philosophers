#include "philosophers.h"


long int    whattimeisit(void)
{
    long int    ms;
    struct timeval  timestruct;

    if (gettimeofday(&timestruct, NULL) == -1)
    {
        printf("Couldn't get time of day.\n");
        return (-1);
    }
    ms = timestruct.tv_sec * 1000 + timestruct.tv_usec / 1000;
    return (ms); 
}

void    *philosopher(void *arg)
{
    t_philo *data;
    int meals;

    meals = 0;
    data = (t_philo *)arg;
    (void)data;
    // if (data->ph_id % 2 != 0)
        // usleep(data->rules->t_eat);
    pthread_mutex_lock(&data->rules->someone_died_m);
    while (data->rules->someone_died == 0)
    {
        pthread_mutex_unlock(&data->rules->someone_died_m);
        pick_fork(data);
        meals++;
        printf("%ld: philo %d is eating.\n", whattimeisit(), data->ph_id);
        usleep(data->rules->t_eat);
        leave_fork(data);
        pthread_mutex_lock(&data->rules->someone_died_m);
        if (meals == data->rules->meals_cap)
            data->rules->someone_died = 1;
    }
    pthread_mutex_unlock(&data->rules->someone_died_m);
    // printf("philosopher n%d said: ''it is currently %ld !''\n", data->ph_id, whattimeisit());
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
    // free(table);
    destroy_cutlery(cutlery);
    // dishcleaner(cutlery);
    return (0);
}


/*
    1. fonction pick up fork (/w message)
    2. fonction put down fork (/w message)
    3. sleeping
    3.5 fonction micro sleep 
    4. thinking
    5. fonction check someone_died

    vérifier la next fourchette aussi
    avant de usleep, verifier si le philo meurt pendant ce laps de temps !
*/