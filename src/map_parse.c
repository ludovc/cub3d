#include "../inc/cub3d.h"

/*controlli:    mappa vuota, 
                caratteri invalidi, 
                numero spawn, 
                mappa non chiusa*/
                
static int	validate_map_chars(char **map, int *spawn_count)
{
	int		y;
	int		x;
	char	c;
	int	 	row_len;
	int		has_errors;

	y = 0;
	has_errors = 0;
	while (map && map[++y])
	{
		row_len = ft_strlen(map[y]);
		x = 0;
		while (++x < row_len)
		{
			c = map[y][x];
			if (!is_valid_tile(c))
			{
				ft_printf("Error: invalid character '%c' in map at line %d, column %d\n", c, y + 1, x + 1);
				has_errors = 1;
			}
			if (is_spawn(c))
				(*spawn_count)++;
		}
	}
	return (has_errors);
}

static char	map_at(char **map, int y, int x)
{
	int	row_len;

	if (y < 0 || x < 0)
		return (' ');
	if (!map || !map[y])
		return (' ');
	row_len = ft_strlen(map[y]);
	if (x >= row_len)
		return (' ');
	return (map[y][x]);
}

static int	has_void_neighbor(char **map, int y, int x)
{
	if (map_at(map, y - 1, x) == ' ')
		return (1);
	if (map_at(map, y + 1, x) == ' ')
		return (1);
	if (map_at(map, y, x - 1) == ' ')
		return (1);
	if (map_at(map, y, x + 1) == ' ')
		return (1);
	return (0);
}

static int	validate_map_closed(char **map)
{
	int		y;
	int		x;
	int		row_len;
	char	c;

	y = 0;
	while (map && map[++y])
	{
		row_len = ft_strlen(map[y]);
		x = 0;
		while (++x < row_len)
		{
			c = map[y][x];
			if (c == '0' || is_spawn(c))
			{
				if (has_void_neighbor(map, y, x))
				{
					ft_printf("Error: no confining wall at line %d, column %d\n", y + 1, x + 1);
					return (1);
				}
			}
		}
	}
	return (0);
}

int	validate_map(char **map)
{
	int	spawn_count;
	int	has_errors;

	spawn_count = 0;
	has_errors = 0;
	if (!map || !map[0])
	{
		ft_printf("Error: empty map\n");
		return (1);
	}
	if (validate_map_chars(map, &spawn_count))
		has_errors = 1;
	if (spawn_count != 1)
	{
		ft_printf("Error: found %d spawns (expected exactly 1)\n", spawn_count);
		has_errors = 1;
	}
	if (validate_map_closed(map))
		has_errors = 1;
	return (has_errors);
}
