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

int	main()
{
	t_game game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "CUB3D");
	game.player.x = WIDTH / 2;
	game.player.y = HEIGHT / 2;
	game.player.color = GREEN;
	
	draw_player(game.mlx, game.win, &game.player);

	mlx_hook(game.win, 17, 0, close_window, NULL);
	mlx_hook(game.win, 2, 1, handle_key, &game);
	mlx_loop(game.mlx);
}
