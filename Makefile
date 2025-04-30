NAME = cub3D
CC = cc

CFLAGS       = -Wall -Wextra -Werror -g -I$(INC_DIR) -DBONUS_MODE=false

# MiniLibX
MLX_DIR      = minilibx-linux
LIBMLX       = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS    = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lz -lm

# libft (external)
LIBFT_REPO   = https://github.com/yuhi-ootani/lifbt_all.git
LIBFT_DIR    = libft
LIBFT        = $(LIBFT_DIR)/libft.a

SRC_DIR = srcs
INC_DIR = includes
OBJ_DIR = objs

LIBFT_DIR = libft
LIBFT = libft/libft.a
INC_DIR = includes
MAIN_DIR = srcs/a_main
PARSER_DIR = srcs/parsing
INIT_GAME_DIR = srcs/init_game
GAME_LOOP_DIR = srcs/mlx_game_loop
KEY_EXIT_DIR = srcs/key_and_exit
UTILS_DIR = srcs/utils

# MINIMAP_SRCS := $(wildcard srcs/minimap/*.c)
# INIT_GAME_SRCS := $(wildcard $(INIT_GAME_DIR)/*.c)
# GAME_LOOP_SRCS := $(wildcard $(GAME_LOOP_DIR)/*.c)
PARSER_SRCS := $(wildcard $(PARSER_DIR)/*.c)

INIT_GAME_SRCS	= 	srcs/init_game/int_player.c srcs/init_game/load_images.c srcs/init_game/start_game.c 
KEY_EXIT_SRCS = 	srcs/key_and_exit/exit_game.c srcs/key_and_exit/free.c srcs/key_and_exit/key_handler.c 
MINIMAP_SRCS = 		srcs/minimap/init_minimap_bonus.c srcs/minimap/minimap_utils_bonus.c \
					srcs/minimap/render_minimap_bonus.c srcs/minimap/render_ply_ray_bonus.c
GAME_LOOP_SRCS =	srcs/mlx_game_loop/game_loop.c srcs/mlx_game_loop/m_move_player.c srcs/mlx_game_loop/m_movement.c \
					srcs/mlx_game_loop/m_rotatoin.c srcs/mlx_game_loop/ra_get_hori_inter.c srcs/mlx_game_loop/ra_get_step.c \
					srcs/mlx_game_loop/ra_get_verti_int.c srcs/mlx_game_loop/ra_ray_direction.c srcs/mlx_game_loop/ra_raycast_compute.c \
					srcs/mlx_game_loop/ra_raycast_helper.c srcs/mlx_game_loop/ra_raycasting.c srcs/mlx_game_loop/re_render_wall.c \
					srcs/mlx_game_loop/re_render.c


SRCS = srcs/a_main/main.c \
		$(INIT_GAME_SRCS) \
		$(KEY_EXIT_SRCS) \
		$(MINIMAP_SRCS) \
		$(GAME_LOOP_SRCS) \
		$(PARSER_SRCS) 


OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME) 

bonus: CFLAGS += -UBONUS_MODE -DBONUS_MODE=true
bonus: all

$(NAME): $(OBJS) $(LIBMLX)
	$(CC) $(CFLAGS)  $(OBJS) $(MLX_FLAGS) $(LIBFT) -o $(NAME)
	
$(LIBMLX) : 
	if [ ! -f $(LIBMLX) ]; then \
		cd $(MLX_DIR) && ./configure && make; \
	fi

$(LIBFT) :
	 @echo "🔍 Checking for libft..."
	 @if [ ! -d "$(LIBFT_DIR)" ]; then \
	 	echo "📥 Cloning libft..."; \
	 	git clone  --quiet $(LIBFT_REPO)  $(LIBFT_DIR); \
	 fi
	 @make -C $(LIBFT_DIR) --silent

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make clean -C $(LIBFT_DIR) --silent; \
	fi
	rm -f $(OBJS)

fclean: clean
	@if [ -d "$(LIBFT_DIR)" ]; then \
		rm -rf $(LIBFT_DIR); \
		echo "🧹 Removing libft directory..."; \
	fi
	rm -f $(NAME)


re: fclean all



.PHONY: all clean fclean bonus re