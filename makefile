CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -I./include

NAME = cub3d.a

LIBFTD = Libft/libft.a

SRC_PATH =	get_next_line.c			\
			get_next_line_utils.c	\
			call.c					\

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