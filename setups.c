#include "philosophers.h"

void    ph_init(t_ph *ph, t_list **list, int nph, t_rules *rules)
{
    int i;

    i = 0;
    while (i != nph)
    {
        (ph + i)->fork = addback(&(*list));
        i++;
    }
    i = 0;
    while (i != nph)
    {
        (ph + i)->meals = 0;
        (ph + i)->ph_id = i + 1;
        (ph + i)->rules = rules;
        if ((ph + i)->ph_id % 2 != 0)
        {
            (ph + i)->first = &(ph + i)->fork->fork_m;
            (ph + i)->second = &(ph + i)->fork->next->fork_m;
        }
        else
        {
            (ph + i)->first = &(ph + i)->fork->next->fork_m;
            (ph + i)->second = &(ph + i)->fork->fork_m;
        }
        i++;
    }
    return ;
}

t_rules init_rules(char **av, int nph)
{
    t_rules rules;

    pthread_mutex_init(&(rules.end_m), NULL);
    pthread_mutex_init(&(rules.success_m), NULL);
    pthread_mutex_init(&(rules.start_m), NULL);
    rules.end = 0;
    rules.success = nph;
    rules.t_death = ft_atoi(av[2]);
    rules.t_eat = ft_atoi(av[3]);
    rules.t_sleep = ft_atoi(av[4]);
    if (av[5])
        rules.cap = ft_atoi(av[5]);
    else
        rules.cap = 0;
    return (rules);
}

void    struct_init(t_ph **ph, pthread_t ***threads, t_rules **rules, char **av)
{
	int i;

	i = 0;
    *threads = malloc(sizeof(pthread_t *) * ft_atoi(av[1]));
	while (i != ft_atoi(av[1]))
	{
        (*threads)[i] = malloc(sizeof(pthread_t));
		i++;
	}
    *ph = malloc(sizeof(t_ph) * ft_atoi(av[1]));
    *rules = malloc(sizeof(t_rules));
    **rules = init_rules(av, ft_atoi(av[1]));
    (*rules)->start = whattimeisit();
    return ;
}
