#include "philosophers.h"

// t_rules init_rules(char **av)
// {
//     t_rules rules;
//     rules.philo_id = ft_atoi(av[1]);
//     rules.t_death = ft_atoi(av[2]);
//     rules.t_eat = ft_atoi(av[3]);
//     rules.t_sleep = ft_atoi(av[4]);
//     if (av[5])
//         rules.meals_cap = ft_atoi(av[5]);
//     else
//         rules.meals_cap = 0;
//     return (rules);

// }

void    *th_init(void *arg)
{
    // int *nth;
    t_mutex *mutex;
    mutex = (t_mutex *)arg;
    // nth = (int *)arg;
    pthread_mutex_lock(&(*mutex).mx);
    printf("\e[0;91mOn est dans le thread n°%d\033[0;39m\n", mutex->nthread);
    pthread_mutex_unlock(&(*mutex).mx);
    pthread_exit(EXIT_SUCCESS);
}

void    thread_init(pthread_t *thread, t_mutex mutex)
{
    pthread_create(thread, NULL, &th_init, &mutex);
    // pthread_join(thread, NULL);
    return ;
}

int main(int ac, char **av)
{
    // int nthread;
    int n_towr;
    pthread_t **tab;
    t_mutex mutex;
    int cpt;

    cpt = 0;
    mutex.nthread = 0;
    n_towr = ft_atoi(av[1]);
    tab = malloc(sizeof(pthread_t *) * n_towr);
    pthread_mutex_init(&mutex.mx, NULL);
    while (cpt < n_towr)
    {
        tab[cpt] = malloc(sizeof(pthread_t));
        cpt++;
    }
    cpt = 0;
    if (tab == NULL)
        return (1);
    // if (ac != 4 || ac != 5)
    // {
    //     printf("Error: too few arguments.");
    //     return (1);
    // }
    while (cpt < n_towr)
    {
        mutex.nthread = cpt;
        thread_init(tab[cpt], mutex);
        cpt++;
        printf("\033[0;92mLe thread n°%d a été créé.\n-----------------\033[0;39m\n", cpt);
    }
    cpt = 0;
    while (cpt < n_towr)
    {
        pthread_join(*tab[cpt], NULL);
        cpt++;
    }
    pthread_mutex_destroy(&mutex.mx);
    return (0);
}