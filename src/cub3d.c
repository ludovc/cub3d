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

void	print_splitted_file(char **settings, char **map)
{
	printf("---------\n");
	print_strarr(settings);
	printf("---------\n");
	print_strarr(map);
	printf("---------\n");
}

void	parsing(t_game *game)
{
	char	**settings;
	char	**map;
	char	**file;

	file = get_file("./maps/scene1.cub");
	// print_strarr(file);
	if (!split_file(file, &settings, &map))
		ft_printf("Errore nello split del file\n");

	free_strarr(file);
	game->settings = extract_settings(settings);
	if (!game->settings)
	{
		ft_printf("Settings invalide\n");
	}
	else if (check_settings(game->settings) == 0)
		ft_printf("Settings invalide\n");
	// check_leftovers();
	free_strarr(settings);

	if (validate_map(map))
		ft_printf("MAPPA INVALIDA\n");
	else
		ft_printf("MAPPA BUONA\n");

	//free_strarr(map);
	game->map = map;
}

void	initialization(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	
	init_image(game);
	
	// init keys
	game->keys.w_pressed = 0;
	game->keys.a_pressed = 0;
	game->keys.s_pressed = 0;
	game->keys.d_pressed = 0;
}

void	free_all(t_game *game)
{
	if (game->settings)
		free_settings(game->settings);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
}

int	main()
{
	t_game game;

	parsing(&game);
	initialization(&game);
	
	if (!find_player_spawn(game.map, &game.player.x, &game.player.y))
	{
		printf("Errore strano: non dovrebbe succedere mai perche gestito nel parsing\n");
	}

	game.player.color = RED;
	
	draw_minimap(&game);									    // per maggiore fluidità del movimento
	mlx_hook(game.win, 17, 0, close_window, NULL);
	mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);		// tasti premuti 
	mlx_hook(game.win, 3, 1L<<1, handle_keyrelease, &game);		// tasti rilasciati
	mlx_loop_hook(game.mlx, game_loop, &game);
	
	mlx_loop(game.mlx);


	free_all(&game);
}
