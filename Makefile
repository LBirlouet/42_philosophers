# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 08:01:51 by lbirloue          #+#    #+#              #
#    Updated: 2024/04/29 11:18:11 by lbirloue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -pthread -g -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3

INCLUDES		=	includes/pipex.h

SRCS			=	srcs/main.c \
					srcs/init.c \
					srcs/utils.c \
					srcs/print.c \
					srcs/one_philo.c \
					srcs/final.c \
					
					
OBJ_DIR			=	objects

OBJS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

GREEN			=	\033[1;92m
RED				=	\033[1;91m
NC				=	\033[0m

${OBJ_DIR}/%.o : %.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o ${NAME}
	@printf "${GREEN}$(NAME) compiled${NC}\n" || (printf "${RED}$(NAME) error${NC}\n" && exit 1)

clean:
	rm -rf $(OBJ_DIR)
	@printf "${RED}all cleaned${NC}\n"
	
fclean: clean
	rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re

# ${OBJ_DIR}/%.o : %.c 
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1 

# all : $(OBJ_DIR) $(NAME)

# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)

# $(NAME) : $(OBJS)
# 	@$(CC) $(OBJS) $(CFLAGS) -o ${NAME} > /dev/null 2>&1 
# 	@printf "${GREEN}$(NAME) compiled${NC}\n" || (printf "${RED}$(NAME) error${NC}\n" && exit 1)

# clean:
# 	@rm -rf $(OBJ_DIR)  > /dev/null 2>&1
# 	@printf "${RED}all cleaned${NC}\n"
	
# fclean: clean
# 	@rm -rf $(NAME)
	
# re: fclean all

# .PHONY: all clean fclean re