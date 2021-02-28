CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -I./include

NAME = cub3d.a

LIBFTD = Libft/libft.a

SRC_PATH =	get_next_line.c			\
			get_next_line_utils.c	\
			calcul.c				\
			hit_1.c					\
			hit_2.c					\
			init.c					\
			main.c					\
			move.c					\
			pixel.c					\
			raycasting.c			\
			rotate.c				\
			sprite.c				\
			sprite_2.c				\
			check_map_2.c			\
			check_map.c				\
			check_params.c			\
			check_params_2.c		\
			get_color_params.c		\
			get_texture.c			\
			save_bmp.c				\
			#call.c					\

SRC = $(addprefix src/,$(SRC_PATH))

OBJ	= $(SRC:.c=.o)

all : libft $(NAME)

clean :
	$(RM) $(OBJ)
	make clean -C Libft

fclean : clean
	$(RM) $(NAME)
	make fclean -C Libft

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)

libft :
	make -C Libft

re : fclean all

.PHONY : all clean re