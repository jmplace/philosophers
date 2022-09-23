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
    pthread_mutex_t someone_died_m;
    int someone_died;
}                   t_rules;

typedef struct      s_philo
{
    t_list  *fork;
    int     ph_id;
    t_rules *rules;
}                   t_philo;


// /*      setup           */

t_rules init_rules(char **av);

/*      routine utilities           */
long int    whattimeisit(void);
void    pick_fork(t_philo *data);
void    leave_fork(t_philo *data);

/*      chained list utilities      */
t_list    *addback(t_list **cutlery);
t_list    *find_last(t_list *list);
void    destroy_cutlery(t_list *cutlery);

/*      cleaning utilities          */
void    dishcleaner(t_list *cutlery);
void    tablecleaner(pthread_t **table, int i);

/*      printer utilities           */
void    dataprinter(t_philo *data);
void    listprinter(t_list *list);
void    ft_print_nl(char *str);

/*      utilities                   */
int     ft_strlen(char *str);
int ft_atoi(char *str);
int ft_is_numeric(char b);
int ft_is_operand(char b);
int ft_is_space(char b);

#endif