#include "strarr.h"

void	print_strarr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}
