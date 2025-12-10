# include "../inc/cub3d.h"

int	map_row_len(const char *row)
{
	int	len;

	len = 0;
	if (!row)
		return (0);
	while (row[len] && row[len] != '\n')
		len++;
	return (len);
}

int	map_height(char **map)
{
	int	h;

	h = 0;
	if (!map)
		return (0);
	while (map[h])
		h++;
	return (h);
}

int	map_max_width(char **map)
{
	int	max;
	int	len;
	int	y;

	max = 0;
	y = 0;
	if (!map)
		return (0);
	while (map[y])
	{
		len = map_row_len(map[y]);
		if (len > max)
			max = len;
		y++;
	}
	return (max);
}

int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_tile(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_spawn(c));
}
