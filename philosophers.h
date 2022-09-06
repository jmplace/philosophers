#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct      s_list
{
    pthread_mutex_t fork;
	struct s_list	*next;
}			        t_list;

typedef struct      s_rules
{
    int t_death;
    int t_eat;
    int t_sleep;
    int last_meal;
    int meals_cap;
}                   t_rules;


// /*      setup           */

// t_rules init_rules(char **av);
// void *thread_1(void *arg);
// void    thread_init(pthread_t *thread, int nthread);

/*      chained list utilities       */
void    addback(t_list **cutlery);
/*      utilities       */
void    ft_print_nl(char *str);
int     ft_strlen(char *str);
int ft_atoi(char *str);
int ft_is_numeric(char b);
int ft_is_operand(char b);
int ft_is_space(char b);

#endif