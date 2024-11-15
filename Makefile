NAME := philo

CC := cc

CFLAGS := -Wall -Wextra -Werror

SRC_DIR := ./sources/

OBJ_DIR := ./objects/

HEADERS := -I ./includes/

SRC_FILES := main.c \
			init_philo.c \
			utils.c \
			philo_routine.c \
			monitoring.c \
			print_msg.c \
			grab_forks.c

SRCS := $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJS := $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(OBJ_DIR):
	@mkdir -p objects

$(NAME): $(OBJS)
	@echo "\e[1;93m Compiling.. ⏳ \e[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME) \
	&& echo "\e[1;92m Philo compiled! 🤩 \e[0m" \
	|| echo "\e[1;91m Failed to compile Philo 😔 \e[0m"

clean:
	@rm -fr $(OBJ_DIR) \
	&& echo "\e[1;96m Removed all object files 🧹 \e[0m" \
	|| echo "\e[1;91m Failed to remove object files 😔 \e[0m"

fclean: clean
	@rm -fr $(NAME) \
	&& echo "\e[1;96m Removed all executables 🧹 \e[0m" \
	|| echo "\e[1;91m Failed to remove executables 😔 \e[0m"

re: fclean all

.PHONY: all, clean, fclean, re