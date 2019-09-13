# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 14:32:21 by bsabre-c          #+#    #+#              #
#    Updated: 2019/09/13 16:22:07 by bsabre-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILL_NAME	= bsabre-c.filler
GRAF_NAME	= grafix.out
FLAGS		= -Wall -Wextra -Werror

# directories
DIR		=	./

# files
SRC_FILLER	= $(DIR)main.c	$(DIR)array.c			$(DIR)algorithm_map.c	\
			  $(DIR)logs.c	$(DIR)fill_ranks.c		$(DIR)algorithm_figure.c\
			  $(DIR)gnl.c
SRC_GRAFIX	= $(DIR)grafix_main.c	$(DIR)grafix_hooks.c	$(DIR)gnl.c		\
			  $(DIR)grafix_exit.c	$(DIR)grafix_reader.c	$(DIR)grafix_img.c
INC_FILLER	= $(DIR)filler.h
INC_GRAFIX	= $(DIR)grafix.h
MLX			= mlx/libmlx.a -lmlx -framework OpenGL -framework AppKit

# libraries
L_FT 		= ./libft/
L_FT_A 		= $(L_FT)libft.a

all :	compile

compile :
		@echo "Compiling libft"
		@make -sC $(L_FT)
		@echo "Combiling filler"
		@gcc $(FLAGS) $(SRC_FILLER) -I$(INC_FILLER) $(L_FT_A) -o $(FILL_NAME)
		@echo "file $(FILL_NAME) was created succesfully"
		@echo "Compiling grafix"
		@gcc $(FLAGS) $(SRC_GRAFIX) -I$(INC_GRAFIX) $(L_FT_A) $(MLX) -o $(GRAF_NAME)
		@echo "file $(GRAF_NAME) was created succesfully"

clean :
		@echo "start cleaning"
		@make clean -sC $(L_FT)
		@rm -rf .DS_Store
		@rm -rf $(L_FT).DS_Store
		@rm -rf filler.trace
		@echo "cleaning finished"

fclean : clean
		@rm -f $(L_FT_A)
		@rm -f $(FILL_NAME)
		@rm -f $(GRAF_NAME)
		@rm -rf log.txt

filler :
		@rm -rf log.txt
		@touch log.txt
		@chmod 777 log.txt
		@./resources/filler_vm 	-f ./resources/maps/map00 	-p1 ./$(FILL_NAME) \
			-p2 ./resources/players/superjeannot.filler  | ./$(GRAF_NAME)

re: fclean compile
