CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3
INCLUDE = -I./includes
VPATH = ./expand ./parsing ./pretoken ./token ./utils_parsing ./ft_dprintf ./clear_error
RM = rm -rf
NAME = test_parsing


SRCS =	ast_redir.c ast_utils.c ast_utils2.c ast.c\
		pretoken_utils.c pretoken_utils2.c pretoken.c\
		automate.c automate2.c token.c\
		ft_calloc.c ft_isalnum.c ft_strchr.c ft_strcmp.c ft_strdup.c\
		ft_strjoin.c ft_strlcpy.c ft_substr.c\
		ft_dprintf.c dprintf_utils.c dprintf_utils2.c\
		expand_environment.c expand_wildcard.c expand.c\
		clear.c\
		main.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR)  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./Music/readline/shlib -lreadline

bonus: all

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) -I./Music/readline

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus