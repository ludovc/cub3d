MLX = minilibx/libmlx.a

all: $(MLX)
	cc -Wall -Wextra -Werror cub3d.c -Lminilibx -lmlx -lXext -lX11

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git minilibx
	- make -C minilibx
