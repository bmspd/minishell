#include "libft.h"
static int	tabpass(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	nbr;
	unsigned long	overflow;

	nbr = 0;
	sign = 1;
	overflow = 922337203685477580;
	i = tabpass(str);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((nbr > overflow || (nbr == overflow
					&& str[i] > '7')) && sign == 1)
			return (-1);
		else if ((nbr > overflow || (nbr == overflow
					&& str[i] > '8')) && sign == -1)
			return (0);
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (nbr * sign);
}
