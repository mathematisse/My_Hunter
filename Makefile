##
## EPITECH PROJECT, 2022
## B-MUL-100-TLS-1-1-myhunter-lucien.pineau
## File description:
## Compile and test my_hunter
##

SRC		=      	main.c			\
			utils.c			\
			cursor_handler.c	\
			duck_handler.c		\
			duck_loop.c		\
			duck_loop_funcs.c	\
			duck_loop_funcs2.c	\
			hunter_handler.c	\
			hunter_loop.c		\
			hunter_click.c		\
			hunter_click_utils.c	\
			hunter_ui.c		\
			hunter_draw.c		\
			hunter_cost.c		\
			hunter_kill.c		\
			hunter_utils.c		\
			props_handler.c

# Variables for compiling

OBJ		=	$(SRC:.c=.o)

NAME		=	my_hunter

GCC		=	gcc -Wall -Werror -Wextra

CSFML		=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

# Compiling functions

all: $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o $(NAME) $(CSFML) -lm

%.o: %.c
	$(GCC) -c $< -o $@

# Cleaning functions

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

# re functions

re: fclean all
