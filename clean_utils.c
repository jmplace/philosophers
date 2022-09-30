#include "philosophers.h"

void    threadscleaner(pthread_t **threads, int i)
{
    int cpt;

    cpt = 0;
    while (cpt < i)
    {
        free(threads[i]);
        cpt++;
    }
    free(threads);
    return ;
}

void    dishcleaner(t_list *cutlery)
{
	t_list	*tmp;
	t_list	*tofree;

	tmp = cutlery;
	while (tmp && tmp->next != cutlery)
	{
		tofree = tmp;
		tmp = tmp->next;
        free(&(tofree->fork_m));
		free(tofree);
	}
    free(&(tmp->fork_m));
	free(tmp);
    // listprinter(cutlery);
    return ;
}