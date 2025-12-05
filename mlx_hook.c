#include "cub3d.h"

int handle_key(int keycode, void *param)
{
	t_game *game = (t_game *)param;
	
	if (keycode == ESC_KEY)
		close_window();
	else if (keycode == W_KEY)
		update_player(game, 0, -1);
	else if (keycode == S_KEY)
		update_player(game, 0, 1);
	else if (keycode == A_KEY)
		update_player(game, -1, 0);
	else if (keycode == D_KEY)
		update_player(game, 1, 0);
    return (0);
}

int	close_window()
{
	exit(0);
	return (0);
}