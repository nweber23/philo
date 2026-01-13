MAKEFLAGS += --silent
NAME = philo_bonus
SRC = main.c utils.c simulation.c cleanup.c init.c actions.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[1;32m"
	@echo "                                      "
	@echo " ██▓███   ██░ ██  ██▓ ██▓     ▒█████  "
	@echo "▓██░  ██▒▓██░ ██▒▓██▒▓██▒    ▒██▒  ██▒"
	@echo "▓██░ ██▓▒▒██▀▀██░▒██▒▒██░    ▒██░  ██▒"
	@echo "▒██▄█▓▒ ▒░▓█ ░██ ░██░▒██░    ▒██   ██░"
	@echo "▒██▒ ░  ░░▓█▒░██▓░██░░██████▒░ ████▓▒░"
	@echo "▒▓▒░ ░  ░ ▒ ░░▒░▒░▓  ░ ▒░▓  ░░ ▒░▒░▒░ "
	@echo "░▒ ░      ▒ ░▒░ ░ ▒ ░░ ░ ▒  ░  ░ ▒ ▒░ "
	@echo "░░        ░  ░░ ░ ▒ ░  ░ ░   ░ ░ ░ ▒  "
	@echo "          ░  ░  ░ ░      ░  ░    ░ ░  "
	@echo "                                      "
	@echo "       BONUS COMPILATION FINISHED     "
	@echo "\033[0m"

$(OBJ_DIR)/%.o: %.c philo.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
