#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct      s_philo
{
    int id;
    int state;
}                   t_philo;


typedef struct      s_rules
{
    int philo_id;
    int t_death;
    int t_eat;
    int t_sleep;
    int t_think;
    int meals_cap;
}                   t_rules;

typedef struct  s_mutex
{
    int nthread;
    pthread_mutex_t mx;
}                   t_mutex;


// /*      setup           */

// t_rules init_rules(char **av);
// void *thread_1(void *arg);
// void    thread_init(pthread_t *thread, int nthread);

/*      utilities       */
int ft_atoi(char *str);
int ft_is_numeric(char b);
int ft_is_operand(char b);
int ft_is_space(char b);

#endif