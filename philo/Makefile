NAME = philo
NAME_BONUS =

SRC = src/main.c \
	src/parsing.c \
	src/utils.c \
	src/init.c

OBJ = $(SRC:.c=.o)

SRC_BONUS =

OBJ_BONUS =

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -fsanitize=address -g3

LIBFT = libft/libft.a

all: $(NAME)

bonus: $(NAME_BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Compiling $(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) compiled"

$(NAME_BONUS): $(OBJ_BONUS)
	@echo "Compiling $(NAME_BONUS)"
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)
	@echo "$(NAME_BONUS) compiled"

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