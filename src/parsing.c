#include "../inc/cub3d.h"

int	check_leftovers(char **settings)
{
	int		i;

	i = 0;
	while (settings[i])
	{
		if (settings[i][0] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	parsing(t_game *game)
{
	char	**settings;
	char	**map;
	char	**file;

	file = get_file("./maps/scene1.cub");
	split_file(file, &settings, &map);
	free_strarr(file);
	game->settings = extract_settings(settings);
	if (!game->settings)
	{
		ft_printf("Settings invalide\n");
		free_strarr(settings);
		free_strarr(map);
		exit(1);
	}
	if (!check_leftovers(settings))
	{
		ft_printf("Settings invalide\n");
		ft_printf("leftovers\n");
		free_strarr(settings);
		free_strarr(map);
		exit(1);
	}
	free_strarr(settings);
	if (!check_settings(game->settings))
	{
		ft_printf("Settings invalide\n");
		free_strarr(map);
		exit(1);
	}
	if (validate_map(map) == 1)
	{
		ft_printf("MAPPA INVALIDA\n");
		free_strarr(map);
		free_settings(game->settings);
		exit(1);
	}
	game->map = map;
	return (1);
}
