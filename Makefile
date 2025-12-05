MLX = minilibx/libmlx.a

all: $(MLX)
	cc -Wall -Wextra -Werror -Iinc src/cub3d.c src/mlx_hook.c src/mlx_draw.c -Lminilibx -lmlx -lXext -lX11 -o cub3d

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git minilibx
	- make -C minilibx
