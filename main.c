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

// void    *th_init(void *arg)
// {
//     t_mutex *mutex;

//     mutex = (t_mutex *)arg;
//     pthread_mutex_lock(&(*mutex).mx);
//     mutex->nthread++;
//     pthread_mutex_unlock(&(*mutex).mx);
//     printf("\e[0;91mL'int dans le mutex est à %d\e[0m\n", mutex->nthread);
//     pthread_exit(EXIT_SUCCESS);
// }

// void    threadinit(pthread_t *thread, t_mutex *mutex)
// {
//     int err;

//     err = pthread_create(thread, NULL, &th_init, mutex);
//     if (err != 0)
//         printf("Un thread n'a pas pu être créé.\n");
//     return ;
// }


int main(int ac, char **av)
{
    int nphilo;
    pthread_t **table;
    t_list *cutlery = NULL;
    int i;

    i = 0;
    nphilo = ft_atoi(av[1]);
    table = malloc(sizeof(pthread_t *) * nphilo);
    while(i != nphilo)
    {
        addback(&cutlery);
        // ft_print_nl("un maillon ajouté");
        i++;
    }
    // i = 0;
    // while(i != (nphilo + 1))
    // {
    //     printf("%p\n", cutlery);
    //     cutlery = cutlery->next;
    //     i++;
    // }
    return (0);
}

// int main(int ac, char **av)
// {
//     int n_towr;
//     pthread_t **tab;
//     t_mutex *mutex;
//     int cpt;
//     // int err;

//     mutex = malloc(sizeof(t_mutex));
//     cpt = 0;
//     mutex->nthread = 0;
//     n_towr = ft_atoi(av[1]);
//     tab = malloc(sizeof(pthread_t *) * n_towr);
//     pthread_mutex_init(&mutex->mx, NULL);
//     while (cpt < n_towr)
//     {
//         tab[cpt] = malloc(sizeof(pthread_t));
//         cpt++;
//     }
//     cpt = 0;
//     if (tab == NULL)
//         return (1);
//     // if (ac != 4 || ac != 5)
//     // {
//     //     printf("Error: too few arguments.");
//     //     return (1);
//     // }
//     while (cpt < n_towr)
//     {
//         threadinit(tab[cpt], mutex);
//         // err = pthread_create(tab[cpt], NULL, &th_init, &mutex);
//         // if (err != 0)
//         //     printf("Un thread n'a pas pu être créé.\n");
//         cpt++;
//         printf("\033[0;92mLe thread n°%d a été créé.\n-----------------\e[0m\n", cpt);
//     }
//     cpt = 0;
//     while (cpt < n_towr)
//     {
//         pthread_join(*tab[cpt], NULL);
//         printf("\e[0;34mWaiting for a thread to end.\e[0m\n");
//         cpt++;
//     }
//     pthread_mutex_destroy(&mutex->mx);
//     return (0);
// }