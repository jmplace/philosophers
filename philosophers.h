#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

#define RED "\x1B[31m"
#define WHT "\x1B[0m"

typedef struct      s_list
{
    pthread_mutex_t fork_m;
	struct s_list	*next;
}			        t_list;

typedef struct      s_rules
{
    long int t_death;
    long int t_eat;
    long int t_sleep;
    int meals_cap;
    long int start;
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

/*      time utilities             */
long int    time_monitor(t_ph *ph);
long int    whattimeisit(void);
void        waiting(long int time, t_ph *ph);

/*      routine utilities          */
void    sleep_time(t_ph *ph, long int time, int flag);
void    lock_f(t_ph *ph);
void    unlock_f(t_ph *ph);
void    ending_c(t_ph *ph);
void    ending_c_f(t_ph *ph);

/*      linked list utilities      */
t_list    *addback(t_list **cutlery);
t_list    *find_last(t_list *list);
void      destroy_list(t_list *cutlery);

/*      cleaning utilities          */
void    dishcleaner(t_list *cutlery);
void    tablecleaner(pthread_t **table, int i);

/*      printer utilities           */
void    phprinter(t_ph *ph);
void    listprinter(t_list *list);

/*      utilities                    */
int     ft_strlen(char *str);
int ft_atoi(char *str);
int ft_is_numeric(char b);
int ft_is_operand(char b);
int ft_is_space(char b);

#endif