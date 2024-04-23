# ----------------------------------En LEGENDE------------------------------------
GREEN = \033[0;32m
GREEN_BOLD = \033[1;32m
BLUE = \033[0;34m
ORANGE = \033[0;38;5;214m
YELLOW = \033[0;33m
CLOSE = \033[0m

# -----------------------------------Makefile------------------------------------
NAME 	   = philo
DEBUG 	   = debug.out
# -----------------------------------Sources-------------------------------------
HEADER	   = includes/philo.h

SRCS	   = philo.c \
				utils.c \
				utils2.c \
				routine.c \
				destroy.c \

SRC	       = ${addprefix sources/, ${SRCS}}

OBJS	   	= ${addprefix objects/, ${SRCS:.c=.o}}
# -----------------------------------Compilation---------------------------------
CC			= cc
FLAGS		= -Wall -Wextra -Werror -pthread -g -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3
RM			= rm -f
FSANITIZE	= -fsanitize=thread -g

# ----------------------------------En LEGENDE------------------------------------
GREEN = \033[0;32m
GREEN_BOLD = \033[1;32m
RED = \033[0;31m
RED_BOLD = \033[1;31m
MAGENTA = \033[0;35m
BLUE = \033[0;34m
ORANGE = \033[0;38;5;214m
YELLOW = \033[0;33m
CLIGNOT = \033[5m
WHITE_BG = \033[47m
CLOSE = \033[0m


TOTAL_FILES 	:= $(words $(BASE) $(SRCS) $(SRCS_bonus))
CURRENT_FILE 	:= 0

define progress_bar_pipex
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    @printf "\r$(MAGENTA)Compiling Philo... ⌛⌛⌛[%-$(TOTAL_FILES)s] %d/%d $(NC)" $$(for i in $$(seq 1 $(CURRENT_FILE)); do printf "="; done) $(CURRENT_FILE) $(TOTAL_FILES)
	@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo "$(YELLOW)\n\nPhilo c'est bon ma gueule 👌\n$(CLOSE)"; fi
endef


# -----------------------------------Rules---------------------------------------

all: $(NAME)

$(NAME): ${FT} ${OBJS} ${HEADER}
	@$(CC)  ${OBJS} -o $(NAME)

${FT}:
	@${MAKE_FT}

objects/%.o: sources/%.c | objects
	@$(CC) $(FLAGS) -c $< -o $@
	$(call progress_bar_pipex)

objects:
	@mkdir -p $@

debug: ${FT} ${OBJS} ${HEADER}
	$(CC) $(FLAGS) $(FSANITIZE) ${OBJS} -o $(DEBUG)

clean:
	@$(RM) -rf objects
	@sleep 0.3
	@echo "\n$(BLUE)🧹🧹🧹 It's clean. 🧹🧹🧹$(CLOSE)"

fclean: clean
	@$(RM) $(NAME) $(DEBUG)
	@sleep 0.6
	@printf "\n$(GREEN_BOLD)🌪🌪🌪 It's super clean. 🌪🌪🌪\n\n$(CLOSE)"

re: fclean all

# -----------------------------------.phony-------------------------------------
.PHONY: all clean fclean re debug bonus
