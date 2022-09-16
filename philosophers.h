#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct      s_list
{
    pthread_mutex_t fork_status;
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

typedef struct      s_philo
{
    t_list  *fork;
    int     ph_id;
    t_rules *rules;
}                   t_philo;


// /*      setup           */

// t_rules init_rules(char **av);

/*      chained list utilities       */
t_list    *addback(t_list **cutlery);
t_list    *find_last(t_list *list);
void    destroy_cutlery(t_list *cutlery);

/*      utilities       */
void  listprinter(t_list *list);
void    dataprinter(t_philo *data);
void    ft_print_nl(char *str);
int     ft_strlen(char *str);
int ft_atoi(char *str);
int ft_is_numeric(char b);
int ft_is_operand(char b);
int ft_is_space(char b);

#endif