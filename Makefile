# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 14:36:31 by pbotargu          #+#    #+#              #
#    Updated: 2024/12/10 15:28:58 by pbotargu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= ircserv

INC_DIR = inc/
SRC_DIR = srcs/
OBJ_DIR = objs/

INC		= $(INC_DIR)Server.hpp \
		  $(INC_DIR)Client.hpp \
		  $(INC_DIR)Channel.hpp \
		  $(INC_DIR)Utils.hpp

SRC		= $(SRC_DIR)Server.cpp \
		  $(SRC_DIR)Client.cpp \
		  $(SRC_DIR)Channel.cpp \
		  $(SRC_DIR)Utils.cpp \
		  $(SRC_DIR)cmds/JOIN.cpp \
		  $(SRC_DIR)cmds/PASS.cpp \
		  $(SRC_DIR)parser.cpp \
		  $(SRC_DIR)main.cpp 

#$ \
		  $(SRC_DIR)cmds/NICK.cpp \
		  $(SRC_DIR)cmds/PRIVMSG.cpp \
		  $(SRC_DIR)cmds/USER.cpp \
		  $(SRC_DIR)cmds/INVITE.cpp \

OBJ = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
DEP = $(OBJ:.o=.d)
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP -g

# Colored output
ERASE	= \033[2K\r
BLUE	= \033[34m
YELLOW	= \033[33m
GREEN	= \033[32m
END		= \033[0m

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/cmds

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp Makefile
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo "$(BLUE)-> $<$(END)"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) made$(END)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Objects removed$(END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)$(NAME) removed$(END)"

re:	fclean all

-include $(DEP)

.PHONY:		all clean fclean re
