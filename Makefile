NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_DIR = minilibx-linux

# allow BONUS_MODE to be set from the command line
ifdef BONUS_MODE
CFLAGS += -DBONUS_MODE=true
endif


MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lz -lm
LIBMLX = $(MLX_DIR)/libmlx_Linux.a
LIBFT_REPO = https://github.com/yuhi-ootani/lifbt_all.git

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

MINIMAP_SRCS := $(wildcard srcs/minimap/*.c)
INIT_GAME_SRCS := $(wildcard $(INIT_GAME_DIR)/*.c)
GAME_LOOP_SRCS := $(wildcard $(GAME_LOOP_DIR)/*.c)
PARSER_SRCS := $(wildcard $(PARSER_DIR)/*.c)


SRCS = $(MAIN_DIR)/main.c \
		$(MINIMAP_SRCS) \
		$(INIT_GAME_SRCS) \
		$(GAME_LOOP_SRCS) \
		$(PARSER_SRCS) \
		srcs/key_and_exit/exit_game.c srcs/key_and_exit/key_handler.c srcs/key_and_exit/free.c


OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME) 

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

bonus: CFLAGS += -DBONUS_MODE=true
bonus: re

.PHONY: all clean fclean bonus ew