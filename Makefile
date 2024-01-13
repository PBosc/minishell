CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDE = -I./includes
VPATH = ./expand ./parsing ./pretoken ./token ./utils_parsing ./ft_dprintf ./clear_error ./redir ./exec ./utils_exec ./builtins ./signal
RM = rm -rf
NAME = minishell


SRCS =	ast_redir.c ast_utils.c ast_utils2.c ast.c\
		pretoken_utils.c pretoken_utils2.c pretoken.c checking.c\
		automate.c automate2.c token.c token_utils.c\
		cd.c echo.c env_utils.c env.c exit.c export.c pwd.c unset.c\
		ft_calloc.c ft_isalnum.c ft_strchr.c ft_strcmp.c ft_strdup.c\
		ft_strjoin.c ft_strlcpy.c ft_substr.c ft_atoi.c\
		ft_dprintf.c dprintf_utils.c dprintf_utils2.c\
		expand_wildcard.c expand.c env_expand.c env_expand_dq.c env_expand_utils.c env_expand_utils1.c expand_utils.c sort_wildcard.c\
		clear.c clear1.c redir.c exec.c exec_cmd.c exec_operations.c\
		exec_utils.c exec_pipes.c path.c\
		split.c init.c get_next_line.c heredoc.c utils.c signal.c\
		handlers.c heredoc_utils.c heredoc_expander.c\
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