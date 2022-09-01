#include "philosophers.h"

int		ft_is_space(char b)
{
	return ((b > 8 && b < 14) || b == 32);
}

int		ft_is_operand(char b)
{
	return ((b == 43) || (b == 45));
}

int		ft_is_numeric(char b)
{
	return (b >= '0' && b <= '9');
}

int		ft_atoi(char *str)
{
	int					i;
	unsigned int		res;
	int					minus;

	i = 0;
	res = 0;
	minus = 1;
	while (ft_is_space(str[i]))
		i++;
	while (ft_is_operand(str[i]))
	{
		if (str[i] == '-')
			minus = -minus;
		i++;
	}
	while (ft_is_numeric(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * minus);
}