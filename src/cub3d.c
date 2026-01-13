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

void	free_all(t_game *game)
{
	if (game->settings)
		free_settings(game->settings);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->menu_img.img)
		mlx_destroy_image(game->mlx, game->menu_img.img);
	if (game->txtrs.n_wall.img)
		mlx_destroy_image(game->mlx, game->txtrs.n_wall.img);
	if (game->txtrs.s_wall.img)
		mlx_destroy_image(game->mlx, game->txtrs.s_wall.img);
	if (game->txtrs.e_wall.img)
		mlx_destroy_image(game->mlx, game->txtrs.e_wall.img);
	if (game->txtrs.w_wall.img)
		mlx_destroy_image(game->mlx, game->txtrs.w_wall.img);
	free_strarr(game->map);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int	main(void)
{
	t_game	game;

	parsing(&game);
	initialization(&game);
	load_textures(&game);
	spawn_player(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_all(&game);
}
