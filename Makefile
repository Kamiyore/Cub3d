
NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_DIR = minilibx-linux

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
UTILS_DIR = srcs/utils

RAY_SRCS := $(wildcard srcs/raycaster/*.c)

SRCS = \
    srcs/a_main/main.c \
    srcs/parsing/reading_file.c \
    srcs/utils/free.c \
    $(RAY_SRCS)

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

.PHONY: all clean fclean