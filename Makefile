BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
RESET = \033[0m

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src
OBJ_DIR = ./obj
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Linking..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BOLD)$(GREEN)$(NAME) compiled successfully!$(RESET)"

all: $(NAME)

clean:
	@echo "$(BOLD)Cleaning...$(RESET)"
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re