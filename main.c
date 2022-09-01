#include "philosophers.h"

rules *init_rules(char **av)
{
    t_rules rules;
    rules.philo_id = ft_atoi(av[0]);
    rules.t_death = ft_atoi(av[1]);
    rules.t_eat = ft_atoi(av[2]);
    rules.t_sleep = ft_atoi(av[3]);
    if (av[4])
        rules.meals_cap = ft_atoi(av[4]);
    else
        rules.meals_cap = 0;
    return (rules);

}

int main(int ac, char **av)
{
    if (ac != 5)
    {
        printf("Error: too few arguments.");
        return (1);
    }
    init_rules(av);

}


/*
NEED TO PROTECT PARSING !!
*/