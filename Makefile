# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 12:13:01 by knemcova          #+#    #+#              #
#    Updated: 2025/04/13 12:25:44 by knemcova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = minilibx-linux

MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lz -lm
LIBMLX = $(MLX_DIR)/libmlx_Linux.a

SRC_DIR = srcs
INC_DIR = includes
OBJ_DIR = objs

LIBFT_DIR = libft
INC_DIR = includes
MAIN_DIR = srcs/a_main

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME) 
$(NAME): $(OBJS) $(LIBMLX)
	$(CC) $(CFLAGS)  $(OBJS) $(MLX_FLAGS) -o $(NAME)
	
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

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LIBS)


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