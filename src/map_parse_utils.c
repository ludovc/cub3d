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
	return (c == '0' || c == '1' || c == '2' || c == '3' || c == ' ' || is_spawn(c));
}

void set_player_dir(t_game *g)
{
	g->player.dirx = cosf(g->player.angle);
	g->player.diry = sinf(g->player.angle);

	// plane perpendicolare alla dir, scalata con tan(FOV/2)
	float k = tanf((float)FOV / 2.0f);
	g->player.planex = -g->player.diry * k;
	g->player.planey =  g->player.dirx * k;
}

// Esempio: dopo find_player_spawn e dopo aver letto il char di spawn
void set_angle_from_spawn(t_game *g, char spawn)
{
	if (spawn == 'N') g->player.angle = -M_PI_2;
	if (spawn == 'S') g->player.angle =  M_PI_2;
	if (spawn == 'E') g->player.angle =  0.0f;
	if (spawn == 'W') g->player.angle =  M_PI;
	set_player_dir(g);
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

void spawn_player(t_game *game)
{
	if(!find_player_spawn(game->map, &game->player.x, &game->player.y))
	{
		printf("An error occurred while spawning\n");
		free_all(game);
		exit(1);
	}
	set_angle_from_spawn(game, game->map[(int)game->player.y][(int)game->player.x]);
	game->player.color = RED;
}
