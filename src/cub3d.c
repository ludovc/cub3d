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

#include <signal.h>
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
	game->keys.left_pressed = 0;
	game->keys.right_pressed = 0;
}

void	free_all(t_game *game)
{
	if (game->settings)
		free_settings(game->settings);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	free_strarr(game->map);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
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
// (assumendo che tu sappia quale lettera era)
static void set_angle_from_spawn(t_game *g, char spawn)
{
    if (spawn == 'N') g->player.angle = -M_PI_2;
    if (spawn == 'S') g->player.angle =  M_PI_2;
    if (spawn == 'E') g->player.angle =  0.0f;
    if (spawn == 'W') g->player.angle =  M_PI;
    set_player_dir(g);
}


int	main()
{
	t_game game;

	parsing(&game);
	initialization(&game);

	game.music_pid = fork();
	if (game.music_pid == 0) {
		execlp("aplay", "aplay", "wav/8bit_hospital.wav", NULL);
		exit(1);
	}
	
	if (!find_player_spawn(game.map, &game.player.x, &game.player.y))
	{
		printf("Errore strano: non dovrebbe succedere mai perche gestito nel parsing\n");
	}
	set_angle_from_spawn(&game, game.map[(int)game.player.y][(int)game.player.x]);

	game.player.color = RED;
	
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
	mlx_hook(game.win, 3, 1L<<1, handle_keyrelease, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);


	free_all(&game);
}
