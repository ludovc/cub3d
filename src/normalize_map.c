#include "../inc/cub3d.h"

int	get_map_max_width(char **arr, int start)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = start;
	while (arr[i])
	{
		len = ft_strlen(arr[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	*pad_line(char *line, int target_width)
{
	char	*padded;
	int		len;
	int		i;

	len = ft_strlen(line);
	padded = malloc(sizeof(char) * (target_width + 1));
	if (!padded)
		return (NULL);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < target_width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[i] = '\0';
	return (padded);
}