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

void	exit_with_error(char *msg, char **settings, char **map, t_settings *s)
{
    if (msg)
        ft_printf("%s\n", msg);
    if (settings)
        free_strarr(settings);
    if (map)
        free_strarr(map);
    if (s)
        free_settings(s);
    exit(1);
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
		exit_with_error("Error: impostazioni mancanti", settings, map, NULL);
	if (!check_leftovers(settings))
		exit_with_error("Error: impostazioni aggiuntive non riconosciute", settings, map, game->settings);
	free_strarr(settings);
	if (!check_settings(game->settings))
		exit_with_error("Error: impostazioni errate", NULL, map, game->settings);
	if (validate_map(map) == 1)
		exit_with_error("Error: mappa invalida", NULL, map, game->settings);

	game->map = map;
	return (1);
}
