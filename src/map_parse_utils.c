#include "../inc/cub3d.h"

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

int	is_valid_tile(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_spawn(c));
}

int	rgb_string_to_int(const char *rgb_str)
{
	int		i;
	int		rgb[3];
	char	**split;

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	if (!rgb_str)
		return (0);
	split = ft_split(rgb_str, ',');
	if (split)
	{
		if (split[0])
			rgb[0] = ft_atoi(split[0]);
		if (split[1])
			rgb[1] = ft_atoi(split[1]);
		if (split[2])
			rgb[2] = ft_atoi(split[2]);
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
	}
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

int	is_wall(t_game *g, int mx, int my)
{
	if (my < 0 || mx < 0)
		return (1);
	if (!g->map || !g->map[my])
		return (1);
	if (mx >= (int)ft_strlen(g->map[my]))
		return (1);
	return (g->map[my][mx] == '1' || g->map[my][mx] == ' ');
}
