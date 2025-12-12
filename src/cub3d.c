/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 cub3d.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: lucasu <lucasu@student.42firenze.it>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/11 16:00:39 by lucasu			   #+#	  #+#			  */
/*	 Updated: 2025/11/11 16:03:20 by lucasu			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**get_map(char *path);

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
		return (0);
	}
	if (!check_leftovers(settings))
	{
		ft_printf("Settings invalide\n");
		ft_printf("leftovers\n");
		free_strarr(settings);
		free_strarr(map);
		return (0);
	}
	free_strarr(settings);
	if (!check_settings(game->settings))
	{
		ft_printf("Settings invalide\n");
		free_strarr(map);
		return (0);
	}
	if (validate_map(map) == 1)
	{
		ft_printf("MAPPA INVALIDA\n");
		free_strarr(map);
		return (0);
	}
	free_strarr(map);
	return (1);
}

void	free_all(t_game *game)
{
	if (game->settings)
		free_settings(game->settings);
}

int	main()
{
	t_game game;

	parsing(&game);

	// game.mlx = mlx_init();
	// game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "CUB3D");
	// game.player.x = WIDTH / 2;
	// game.player.y = HEIGHT / 2;
	// game.player.color = GREEN;
	
	// draw_player(game.mlx, game.win, &game.player);

	// mlx_hook(game.win, 17, 0, close_window, NULL);
	// mlx_hook(game.win, 2, 1, handle_key, &game);
	// mlx_loop(game.mlx);
	free_all(&game);
}
