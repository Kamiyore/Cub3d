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
LOAD_IMAGE_DIR = srcs/load_image
DESIGN_DIR = srcs/design
RAYCASTER_DIR = srcs/raycaster
UTILS_DIR = srcs/utils

<<<<<<< HEAD
<<<<<<< HEAD
RAY_SRCS := $(wildcard srcs/raycaster/*.c)
MINIMAP_SRCS := $(wildcard srcs/minimap/*.c)

SRCS = \
    srcs/a_main/main.c \
    srcs/parsing/reading_file.c \
    srcs/utils/free.c \
    $(RAY_SRCS) \
	$(MINIMAP_SRCS)
=======
=======
>>>>>>> kiki
SRCS = $(MAIN_DIR)/main.c \
		$(PARSER_DIR)/map_validation.c $(PARSER_DIR)/set_config_and_map.c $(PARSER_DIR)/reading_file.c $(PARSER_DIR)/rgb_validation.c $(PARSER_DIR)/map_layout.c\
		 $(LOAD_IMAGE_DIR)/parsing_images.c $(LOAD_IMAGE_DIR)/key_handler.c \
		 $(DESIGN_DIR)/floor_and_ceiling.c \
		 $(RAYCASTER_DIR)/get_step.c $(RAYCASTER_DIR)/get_hori_inter.c $(RAYCASTER_DIR)/get_verti_int.c $(RAYCASTER_DIR)/minicub.c $(RAYCASTER_DIR)/player_direction.c $(RAYCASTER_DIR)/ray_direction.c $(RAYCASTER_DIR)/raycast_helper.c $(RAYCASTER_DIR)/render.c \
		 $(UTILS_DIR)/free.c \
<<<<<<< HEAD
>>>>>>> debd40837a4cc76c5c5113dbaecfd60a72b24de3
=======
>>>>>>> kiki

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