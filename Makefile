all:
	cc -Wall -Wextra -Werror cub3d.c -Lminilibx -lmlx -lXext -lX11
