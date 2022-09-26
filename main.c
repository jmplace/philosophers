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
    ms = (timestruct.tv_sec * 1000) + (timestruct.tv_usec / 1000);
    return (ms); 
}

void    cutlery_init(t_ph *ph, t_list **cutlery, int nph)
{
    int i;

    i = 0;
    while (i != nph)
    {
        (ph + i)->fork = addback(&(*cutlery));
        i++;
    }
    return ;
}

void    *philosopher(void *arg)
{
    t_ph *data;
    int meals;

    meals = 0;
    data = (t_ph *)arg;
    (void)data;
    data->last_meal = whattimeisit();
    printf("%ld: ph %d is awake.\n", whattimeisit(), data->ph_id);
    if (data->ph_id % 2 != 0)
        usleep(data->rules->t_sleep);
    pthread_mutex_lock(&data->rules->end_m);
    while (data->rules->end == 0)
    {
        pthread_mutex_unlock(&data->rules->end_m);

        // printf("%ld: %d is stuck here.\n", whattimeisit(), data->ph_id);
        /*     MANGER -- DEBUT                  */
        if (data->rules->end != 0)
        {
            printf("(%d): Someone died: stopping the simulation.\n", data->ph_id);
            leave_fork(data);
            pthread_exit(EXIT_SUCCESS);
        }
        pick_fork(data);
        if (data->rules->end != 0)
        {
            printf("(%d): Someone died: stopping the simulation.\n", data->ph_id);
            leave_fork(data);
            pthread_exit(EXIT_SUCCESS);
        }
        meals++;
        printf("%ld %d is eating.\n", whattimeisit(), data->ph_id);
        data->last_meal = whattimeisit();
        sleep_time(data, data->rules->t_eat, 3);
        leave_fork(data);
        /*     MANGER -- FIN                    */
        
        /*     SLEEP -- DEBUT                   */
        sleep_time(data, data->rules->t_sleep, 1);
        /*     SLEEP -- FIN                     */

        /*     THINK -- DEBUT                   */
        sleep_time(data, 0, 2);
        /*     THINK -- FIN                     */

        pthread_mutex_lock(&data->rules->end_m);
        printf("%d hasn't been eating for %ld msec.\n", data->ph_id, (whattimeisit() - data->last_meal));
        if ((whattimeisit() - data->last_meal) > data->rules->t_death)
        {
            printf("(%d): Je suis mort de faim ! (pas mangé depuis %ldmsec)\n", data->ph_id, (whattimeisit() - data->last_meal));
            data->rules->end = 1;
        }
        if (meals == data->rules->meals_cap)
        {
            printf("(%d): J'ai plus faim ! (%d repas)\n", data->ph_id, meals);
            data->rules->end = 2;
        }
    }
    pthread_mutex_unlock(&data->rules->end_m);
    // printf("philosopher n%d said: ''it is currently %ld !''\n", data->ph_id, whattimeisit());
    pthread_exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    int nph;
    pthread_t **table;
    t_list *cutlery = NULL;
    t_rules *rules = NULL;
    t_ph *ph = NULL;
    int i;
    int err;

    i = 0;
    if (ac == 0)
        return (0);
    err = 0;
    nph = ft_atoi(av[1]);
    table = malloc(sizeof(pthread_t *) * nph);
    ph = malloc(sizeof(t_ph) * nph);
    rules = malloc(sizeof(t_rules));
    *rules = init_rules(av);
    cutlery_init(ph, &cutlery, nph);
    while(i != nph)
    {
        table[i] = malloc(sizeof(pthread_t));
        (ph + i)->ph_id = i + 1;
        (ph + i)->rules = rules;
        pthread_create(table[i], NULL, philosopher, (ph + i));
        i++;
    }
    i = 0;
    while(i != nph)
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
    avant de usleep, verifier si le ph meurt pendant ce laps de temps !
*/