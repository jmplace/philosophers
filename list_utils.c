#include "philosophers.h"

void    addback(t_list **cutlery)
{
    t_list *node;
    t_list *last;

    node = (t_list *)malloc(sizeof(t_list));
    pthread_mutex_init(&(node->fork), NULL);
    if (!(*cutlery))
    {
        node->next = node;
        *cutlery = node;
        return ;
    }
    last = (*cutlery);
    while (last->next != *cutlery)
        last = last->next;
    last->next = node;
    node->next = *cutlery;
    return ;
}