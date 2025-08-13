NAME := minishell
CC := clang
CFLAGS := -Wall -Wextra -Werror -g
LDFLAGS := -lreadline -ltermcap -lncurses -L ./includes/libft/ -lft

SRC_PATH := sources
OBJ_PATH := objects

LIBFT := includes/libft/libft.a

SRC := $(shell find $(SRC_PATH) -name '*.c')
OBJ := $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))

INC := -I ./includes/ -I ./includes/libft/

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C ./includes/libft/

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJ_PATH)
	$(MAKE) clean -C ./includes/libft/

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C ./includes/libft/

re: fclean all

.PHONY: all re clean fclean
