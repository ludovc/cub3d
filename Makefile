NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../inc -g
MLX_FLAGS = -Iminilibx -Lminilibx -lmlx -lXext -lX11 -lm

SRCDIR = src
OBJDIR = obj
INCDIR = inc

MLX = minilibx/libmlx.a
LIBFT = libft/libft.a

SRCS = 	src/check_settings.c \
		src/col_draw.c \
		src/cub3d.c \
		src/extract_cub_section.c \
		src/extract_settings.c \
		src/game_loop.c \
		src/get_file.c \
		src/init.c \
		src/init_load_textures.c \
		src/map_parse.c \
		src/map_parse_utils.c \
		src/minimap_draw.c \
		src/minimap_grid.c \
		src/mlx_hook.c \
		src/normalize_map.c \
		src/parsing.c \
		src/raycasting.c \
		src/render.c \
		src/spawn.c \
		src/split_file.c \
		src/strarr/free_strarr.c \
		src/strarr/print_strarr.c \
		src/strarr/strarr_append.c \
		src/strarr/strarr_dup.c \
		src/strarr/strarr_remove.c \
		src/strarr/strarr_remove2.c \
		src/check_extension.c \

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
CYAN = \033[36m
RESET = \033[0m


all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@printf "$(YELLOW)Linking executable...$(RESET)\n"
	@$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@printf "$(GREEN)✓ Successfully built $(NAME)$(RESET)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\r\033[K$(CYAN)Compiling: $(GREEN)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r\033[K$(GREEN)✓ Compiled: $<$(RESET)\n"

$(LIBFT):
	@printf "$(YELLOW)Building libft...$(RESET)\n"
	@$(MAKE) -C libft --no-print-directory
	@printf "$(GREEN)✓ Successfully built libft$(RESET)\n"

$(MLX):
	@if [ ! -d "minilibx" ]; then \
		printf "$(YELLOW)Downloading MLX library...$(RESET)\n"; \
		git clone https://github.com/42Paris/minilibx-linux.git minilibx; \
	fi
	@printf "$(YELLOW)Building MLX...$(RESET)\n"
	@$(MAKE) -C minilibx --no-print-directory
	@printf "$(GREEN)✓ Successfully built MLX$(RESET)\n"


clean:
	@printf "$(RED)Cleaning...$(RESET)\n"
	@$(MAKE) clean -C libft --no-print-directory 2>/dev/null || true
	@$(MAKE) clean -C minilibx --no-print-directory 2>/dev/null || true
	@rm -rf $(OBJDIR)
	@printf "$(GREEN)✓ Clean completed$(RESET)\n"

fclean: clean
	@$(MAKE) fclean -C libft --no-print-directory 2>/dev/null || true
	@rm -f $(NAME)
	@printf "$(GREEN)✓ Full clean completed$(RESET)\n"

re: fclean all

info:
	@printf "$(BLUE)Project: $(NAME)$(RESET)\n"
	@printf "$(BLUE)Sources found:$(RESET)\n"
	@printf "$(CYAN)$(SRCS)$(RESET)\n"
	@printf "$(BLUE)Objects to build:$(RESET)\n"
	@printf "$(CYAN)$(OBJS)$(RESET)\n"

deps: 
	@$(MAKE) fclean -C libft --no-print-directory 2>/dev/null || true
	@$(MAKE) clean -C minilibx --no-print-directory 2>/dev/null || true
	@$(MAKE) $(MLX) $(LIBFT)

.PHONY: all clean fclean re info deps

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --verbose ./cub3D ./maps/scene1.cub

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D ./maps/scene1.cub
