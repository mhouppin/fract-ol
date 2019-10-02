# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/04/13 10:47:56 by mhouppin     #+#   ##    ##    #+#        #
#    Updated: 2019/10/02 09:52:48 by mhouppin    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME=fractol

OBJECTS=main.o string.o assert.o fractol.o hooks.o graphic_tools.o colors.o \
		draw.o draw_fractal.o

ifeq ($(shell uname -s),Darwin)
	MLX_DIR=macos_minilibx
	LD_FLAGS=-framework OpenGL -framework Appkit
else
	MLX_DIR=linux_minilibx
	LD_FLAGS=-lXext -lX11
endif

all: $(NAME)

$(NAME): $(OBJECTS) libmlx.a
	gcc -Ofast -o $@ $^ $(LD_FLAGS)

fractol.h.gch: fractol.h
	gcc -Wall -Wextra -Werror -o $@ $<

%.o: %.c fractol.h.gch
	gcc -Wall -Wextra -Werror -O2 -c -o $@ $<

libmlx.a:
	make -C $(MLX_DIR) && cp $(MLX_DIR)/libmlx.a ./

clean:
	make clean -C $(MLX_DIR)
	rm -f libmlx.a
	rm -f $(OBJECTS)
	rm -f fractol.h.gch

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
