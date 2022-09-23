#include "philosophers.h"

int     ft_strlen(char *str)
{
    size_t i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

void    ft_print_nl(char *str)
{
    int cnt;
    // int voidd;

    cnt = ft_strlen(str) + 1;
    write(1, str, cnt);
    write(1, "\n", 1);
    // (void)voidd;
    return ;
}