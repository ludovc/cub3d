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
