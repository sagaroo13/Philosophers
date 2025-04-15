NAME = philo

SRC = src/main.c \
	src/parsing.c \
	src/utils1.c \
	src/utils2.c \
	src/utils3.c \
	src/init.c \
	src/dinner.c \
	src/synchro.c \
	src/actions.c \
	src/print_status.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Compiling $(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) compiled"

clean:
	@echo "Cleaning objects"
	@rm -f $(OBJ)
	@echo "Done"

fclean: clean
	@echo "Cleaning executables"
	@rm -f $(NAME)
	@echo "Done"

re: fclean all

.PHONY: all bonus clean fclean re