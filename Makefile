# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 14:36:31 by pbotargu          #+#    #+#              #
#    Updated: 2024/12/23 15:27:02 by anovio-c         ###   ########.fr        #
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
		  $(SRC_DIR)signals.cpp \
		  $(SRC_DIR)cmds/Invite.cpp \
		  $(SRC_DIR)cmds/SendFile.cpp \
		  $(SRC_DIR)cmds/Join.cpp \
		  $(SRC_DIR)cmds/Topic.cpp \
		  $(SRC_DIR)cmds/Kick.cpp \
		  $(SRC_DIR)cmds/Pass.cpp \
		  $(SRC_DIR)cmds/PrivMsg.cpp \
		  $(SRC_DIR)cmds/User.cpp \
		  $(SRC_DIR)cmds/Nick.cpp \
		  $(SRC_DIR)cmds/Mode.cpp \
		  $(SRC_DIR)parser.cpp \
		  $(SRC_DIR)main.cpp 

OBJ = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
DEP = $(OBJ:.o=.d)
CC = g++ 
CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -pedantic -MMD -MP -g 

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

debug:
	valgrind -s --tool=memcheck --leak-check=full --track-fds=yes --track-origins=yes --show-leak-kinds=all ./$(NAME)

git: fclean
	@read -p "Enter commit message: " commit_message; \
	git add *; \
	git commit -m "$$commit_message"
	git push

re:	fclean all

-include $(DEP)

.PHONY:		all clean fclean debug git re
