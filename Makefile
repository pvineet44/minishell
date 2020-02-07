# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparekh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 12:43:24 by vparekh           #+#    #+#              #
#*   Updated: 2020/02/07 11:34:22 by                  ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

BINARY = minishell

LIBFT = ./libft/libft.a
LIBFT_SRC := $(wildcard libft/*.c)
LIBFT_OBJ := $(patsubst libft/%.c, libft/%.o, $(LIBFT_SRC))

#COMP = gcc -Wall -Wextra -Werror -fsanitize=address -g3
COMP = gcc -Wall -Wextra -Werror  -g3
INCLUDES = -Iincludes -Llibft -lft
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, obj/%.o, $(SRC))
GREEN='\033[01;32m'
RESET='\033[00m'

all: $(BINARY)

$(BINARY): $(LIBFT) $(MLX) $(OBJ)
	@echo  "$(GREEN).................Making minishell................ $(RESET)"
	$(COMP) $(INCLUDES) $(OBJ) $(LIBFT) -o $(BINARY)

$(LIBFT): $(LIBFT_OBJ)
	@echo  "$(GREEN).................Making Libft.................... $(RESET)"
	ar rcs $(LIBFT) $(LIBFT_OBJ)

libft/%.o: libft/%.c
	$(COMP) -Iincludes -c $< -o $@

obj/%.o: src/%.c
	mkdir -p obj
	$(COMP) -Iincludes -c $< -o $@
norme:
	norminette src/*
	norminette includes/*

clean: 
		rm -rf libft/*.o obj/*

fclean: clean
	rm -rf $(BINARY) *.dSYM $(LIBFT)

re: fclean all

