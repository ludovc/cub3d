#include "../inc/cub3d.h"

int handle_keypress(int keycode, void *param)
{
	t_game *game = (t_game *)param;
	
	if (keycode == ESC_KEY)
		close_window();
	else if (keycode == W_KEY)
		game->keys.w_pressed = 1;
	else if (keycode == S_KEY)
		game->keys.s_pressed = 1;
	else if (keycode == A_KEY)
		game->keys.a_pressed = 1;
	else if (keycode == D_KEY)
		game->keys.d_pressed = 1;
    return (0);
}

int handle_keyrelease(int keycode, void *param)
{
	t_game *game = (t_game *)param;
	
	if (keycode == W_KEY)
		game->keys.w_pressed = 0;
	else if (keycode == S_KEY)
		game->keys.s_pressed = 0;
	else if (keycode == A_KEY)
		game->keys.a_pressed = 0;
	else if (keycode == D_KEY)
		game->keys.d_pressed = 0;
    return (0);
}

int game_loop(void *param)
{
	t_game *game = (t_game *)param;
	int moved = 0;
	
	// Controlla tutti i tasti premuti e muovi di conseguenza
	if (game->keys.w_pressed)
	{
		update_player(game, 0, -1);
		moved = 1;
	}
	if (game->keys.s_pressed)
	{
		update_player(game, 0, 1);
		moved = 1;
	}
	if (game->keys.a_pressed)
	{
		update_player(game, -1, 0);
		moved = 1;
	}
	if (game->keys.d_pressed)
	{
		update_player(game, 1, 0);
		moved = 1;
	}
	
	// Se non c'è stato movimento, ridisegna comunque per mantenere il frame rate
	if (!moved)
		draw_minimap(game);
		
	return (0);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_all(game);
	exit(0);
	return (0);
}
