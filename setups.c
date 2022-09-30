#include "philosophers.h"

void    list_init(t_ph *ph, t_list **list, int nph)
{
    int i;

    i = 0;
    while (i != nph)
    {
        (ph + i)->fork = addback(&(*list));
        i++;
    }
    return ;
}

void    struct_init(t_ph *ph, t_list **list, t_rules *rules)