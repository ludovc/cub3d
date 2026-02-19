/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <lucasu@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:43:53 by lucasu            #+#    #+#             */
/*   Updated: 2026/02/19 16:50:13 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	input_validation(int argc, char **argv)
{
    int	fd;

    if (argc != 2)
    {
        ft_printf("Uso: ./cub3d <file.cub>\n");
        return(1);
    }
    if (check_extension(argv[1], ".cub"))
    {
        ft_printf("Errore: il file deve avere estensione .cub\n");
        return(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        ft_printf("Errore: file '%s' non trovato\n", argv[1]);
        return(1);
    }
    close(fd);
    return(0);
}

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

int	parsing(t_game *game, char *cub)
{
	char	**settings;
	char	**map;
	char	**file;

	file = get_file(cub);
	split_file(file, &settings, &map);
	free_strarr(file);
	game->settings = extract_settings(settings);
	if (!game->settings)
		exit_with_error("Error: impostazioni mancanti", settings, map, NULL);
	if (!check_leftovers(settings))
		exit_with_error("Error: impostazioni aggiuntive non riconosciute",
			settings, map, game->settings);
	free_strarr(settings);
	if (!check_settings(game->settings))
		exit_with_error("Error: impostazioni errate", NULL, map,
			game->settings);
	if (validate_map(map) == 1)
		exit_with_error("Error: mappa invalida", NULL, map, game->settings);
	game->map = map;
	return (1);
}
