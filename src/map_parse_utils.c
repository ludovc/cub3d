# include "../inc/cub3d.h"

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
		len = ft_strlen(map[y]);
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

int find_player_spawn(char **map, float *x, float *y)
{
	int row, col;
	
	if (!map || !x || !y)
		return (0);
		
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (is_spawn(map[row][col]))
			{
				*x = (float)col + 0.5f;  // centro
				*y = (float)row + 0.5f; 
				return (1);
			}
			col++;
		}
		row++;
	}
	return (0);  // Spawn non trovato
}
