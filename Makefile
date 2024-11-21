# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 14:36:31 by pbotargu          #+#    #+#              #
#    Updated: 2024/11/21 14:37:09 by pbotargu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED = \033[1;31m
MAGENTA = \033[1;35m
BLUE = \033[38;5;75m
ORIGINAL = \033[0m

CPP = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 -g
SRC = main.cpp
RM = rm -rf

#DIRECTORIES
D_OBJ = obj
OBJ = $(addprefix $(D_OBJ)/, $(SRC:.cpp=.o))
DEP = $(addprefix $(D_OBJ)/, $(SRC:.cpp=.d))

all: dir $(NAME)

-include $(DEP)

dir:
		@mkdir -p $(D_OBJ)

# Construcción de los objetos
$(D_OBJ)/%.o: %.cpp Makefile
		@$(CPP) $(FLAGS) -MMD -MP -c $< -o $@
		@echo "$(GREEN)[OK]             $(BLUE).o Correctly done!"

# Creación del ejecutable
$(NAME): $(OBJ)
		@$(CPP) $(FLAGS) $(OBJ) -o $(NAME)
		@echo "$(GREEN)[OK]             $(BLUE)Project $(NAME) successfully compiled!!"

clean:
		@$(RM) $(D_OBJ)
		@echo "$(GREEN)[OK]             $(RED)Cleaned successfully!"

fclean: clean
		@$(RM) $(NAME)
		@echo "$(GREEN)[OK]             $(RED)All removed successfully!"

re: fclean all

.PHONY: all clean fclean re
