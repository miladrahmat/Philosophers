NAME := philo

CC := cc

CFLAGS := -g -Wall -Wextra -Werror

SRC_DIR := ./sources/

OBJ_DIR := ./objects/

HEADERS := -I ./includes/

SRC_FILES := main.c \
			init_philo.c \
			utils.c

SRCS := $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJS := $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(OBJ_DIR):
	@mkdir -p objects

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)

clean:
	@rm -fr $(OBJ_DIR)

fclean: clean
	@rm -fr $(NAME)

re: clean all

.PHONY: all, clean, fclean, re