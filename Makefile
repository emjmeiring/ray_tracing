# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomeirin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/15 12:42:28 by jomeirin          #+#    #+#              #
#    Updated: 2016/07/26 14:40:30 by jomeirin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g

NAME = rt

SRC = ./main.c ./rt_src/maths.c ./rt_src/intersection.c ./rt_src/init.c ./rt_src/output.c ./get_scene/my_get.c ./get_scene/get_next_line.c

RM = rm -f

MACMLX = -lm -lmlx -framework OpenGL -framework AppKit
LIXMLX = -lm -lmlx -lXext -lX11

INC = -I ./incledes/ /usr/include/X11 -I ./

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re


all: $(NAME)

%.o: %.c
	@echo "Linking\t\033[33m$@\033[0m"
	@$(CC) $(FLAG) -c -o $@ $^ $(INC)

$(NAME): $(OBJ)
		@echo "Compiled the pieces together..."
ifeq ($(shell uname), Linux)
		@$(CC) $(FLAG) $(OBJ) -o $@ $(INC) $(LIXMLX)
else
		@$(CC) $(FLAG) $(OBJ) -o $@ $(INC) $(MACMLX)
endif
		@echo "\033[32mDone!\033[0m\nManufactured\t\033[31m$@\033[0m..."

clean:
		@echo "Cleaning\t\033[34m$(NAME)\033[m"
		@$(RM) $(OBJ)
		#@cd utils/ && rm -f
		#@cd src/ && rm -f
		@echo "**********Done!********"

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
