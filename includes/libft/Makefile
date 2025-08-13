NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
AR = ar rcs
RM = rm -f

FILES = ft_bzero \
		ft_isalnum \
		ft_isalpha \
		ft_isdigit \
		ft_itoa \
		ft_printf \
		ft_printf_utils \
		ft_strchr \
		ft_strcmp \
		ft_strdup \
		ft_strjoin \
		ft_strlcpy \
		ft_strlen \
		ft_strncmp \
		ft_strtok \
		ft_strtrim \
		ft_substr

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

m: $(NAME)

all: m

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
