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
    int meals_cap;
    // pthread_mutex_t start_m;
    // int start;
    pthread_mutex_t end_m;
    int end;
}                   t_rules;

typedef struct      s_ph
{
    t_list  *fork;
    long int last_meal;
    int     ph_id;
    t_rules *rules;
}                   t_ph;


// /*      setup           */
void    cutlery_init(t_ph *ph, t_list **cutlery, int nph);
t_rules init_rules(char **av);

/*      routine utilities           */
long int    whattimeisit(void);
void    sleep_time(t_ph *data, long int time, int flag);
void    pick_fork(t_ph *data);
void    leave_fork(t_ph *data);
void    waiting(long int time);

/*      chained list utilities      */
t_list    *addback(t_list **cutlery);
t_list    *find_last(t_list *list);
void    destroy_cutlery(t_list *cutlery);

/*      cleaning utilities          */
void    dishcleaner(t_list *cutlery);
void    tablecleaner(pthread_t **table, int i);

/*      printer utilities           */
void    dataprinter(t_ph *data);
void    listprinter(t_list *list);
void    ft_print_nl(char *str);

/*      utilities                    */
int     ft_strlen(char *str);
int ft_atoi(char *str);
int ft_is_numeric(char b);
int ft_is_operand(char b);
int ft_is_space(char b);

#endif