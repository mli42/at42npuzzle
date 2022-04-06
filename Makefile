# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mli <mli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 13:40:21 by mli               #+#    #+#              #
#    Updated: 2022/04/04 15:22:30 by mli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EOC = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[93m
DBLUE = \033[94m
PURPLE = \033[95m
CYAN = \033[96m

# ############################################################################ #

NAME = n-puzzle

SRCS_PATH = srcs/

CC = clang++
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -MMD

ifeq ($(f), debug)
	CFLAGS += -fsanitize=address -g3
endif

FILES = main.cpp parsing.cpp utils.cpp map_generation.cpp map_solvability.cpp
SRCS = ${addprefix ${SRCS_PATH}, ${FILES}}

SRCS_FILES = ${addprefix , ${SRCS}}

OBJS_PATH = .obj/
OBJS = ${addprefix ${OBJS_PATH}, ${FILES:.cpp=.o}}

MMD_FILES = ${OBJS:.o=.d}

all:
	@printf "$(BOLD)Make $(RED)$(NAME)$(EOC): "
	@echo "$(BOLD)with$(EOC) $(GREEN)$(CC)$(EOC) $(CYAN)$(CFLAGS)$(EOC): "
	@make ${NAME}

$(NAME): ${OBJS_PATH} ${OBJS}
	@echo ""
	@${CC} ${CFLAGS} -o $@ ${OBJS}

${OBJS_PATH}:
	@mkdir -p $@

${OBJS_PATH}%.o: ${SRCS_PATH}%.cpp
	@${CC} ${CFLAGS} -c $< -o $@
	@printf "$(GREEN)▓$(EOC)"

clean:
	@echo "$(BOLD)$(YELLOW)Remove......... |$(GREEN)| done$(EOC)"
	@rm -rf ${OBJS_PATH}

fclean: clean
	@echo "$(BOLD)$(YELLOW)Remove all..... |$(GREEN)| done$(EOC)"
	@rm -rf $(NAME)

re: fclean all

-include ${MMD_FILES}

.PHONY: all clean fclean re
