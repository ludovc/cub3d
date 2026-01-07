#include "../inc/cub3d.h"

static int handle_menu_keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		close_window(game);
	else if (keycode == ENTER_KEY || keycode == SPACE_KEY)
	{
		game->state = PLAYING;
		soundtrack(game);
	}
	return (0);
}

int handle_keypress(int keycode, void *param)
{
	t_game *game = (t_game *)param;
	
	if (game->state == MENU)
		return handle_menu_keypress(keycode, game);
	if (keycode == ESC_KEY)
		close_window(game);
	else if (keycode == W_KEY)
		game->keys.w_pressed = 1;
	else if (keycode == S_KEY)
		game->keys.s_pressed = 1;
	else if (keycode == A_KEY)
		game->keys.a_pressed = 1;
	else if (keycode == D_KEY)
		game->keys.d_pressed = 1;
	else if (keycode == LEFT_ARROW_KEY)
		game->keys.left_pressed = 1;
	else if (keycode == RIGHT_ARROW_KEY)
		game->keys.right_pressed = 1;
	else if (keycode == ENTER_KEY)
		game->keys.enter_pressed = 1;
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
	else if (keycode == LEFT_ARROW_KEY)
		game->keys.left_pressed = 0;
	else if (keycode == RIGHT_ARROW_KEY)
		game->keys.right_pressed = 0;
    return (0);
}

int close_window(void *param)
{
    t_game *game;
    game = (t_game *)param;
    free_all(game);
    exit(0);
    return (0);
}