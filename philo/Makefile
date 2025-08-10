NAME = philo
SRC = 
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes/

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c includes/philo.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BONUS_OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re