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

/*      setup           */
void init_rules(char **av);

/*      utilities       */
int ft_atoi(char *str);
int ft_is_numeric(char b);
int ft_is_operand(char b);
int ft_is_space(char b);

#endif