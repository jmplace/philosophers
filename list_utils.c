#include "philosophers.h"

void  listprinter(t_list *list)
{
    t_list *visiting;
    int i;

    i = 1;
    printf("Welcome to listprinter!\n");
    printf("visiting node #%d : address %p\nvisiting next : %p\n", i, list, list->next);
    i++;
    visiting = list->next;
    while (visiting != list)
    {
        printf("visiting node #%d : address %p\nvisiting next : %p\n", i, visiting, visiting->next);
        i++;
        visiting = visiting->next;
    }
    return ;
}

t_list    *find_last(t_list *list)
{
    t_list *last;

    last = list;
    while (last->next != list)
        last = last->next;
    return (last);
}

t_list    *addback(t_list **cutlery)
{
    t_list *node;
    t_list *last;

    node = (t_list *)malloc(sizeof(t_list));
    pthread_mutex_init(&(node->fork_status), NULL);
    if (!(*cutlery))
    {
        node->next = node;
        *cutlery = node;
        return (node);
    }
    last = find_last(*cutlery);
    last->next = node;
    node->next = *cutlery;
    return (node);
}

void    destroy_cutlery(t_list *cutlery)
{
    t_list *last;
    t_list *tmp;

    last = find_last(cutlery);
    while (cutlery != last)
    {
        pthread_mutex_destroy(&(cutlery->fork_status));
        tmp = cutlery;
        cutlery = cutlery->next;
        free(tmp);
    }
    pthread_mutex_destroy(&(cutlery->fork_status));
    free(cutlery);
    return ;
}