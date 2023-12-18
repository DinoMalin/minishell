NAME = minishell
LIBFT = lib/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -Llib -lft -lreadline
IFLAGS = -Iinclude


SRC =	src/main.c \
		src/builtins/ft_cd.c \
		src/builtins/ft_echo.c \
		src/builtins/ft_env.c \
		src/builtins/ft_exit.c \
		src/builtins/ft_export.c \
		src/builtins/ft_pwd.c \
		src/builtins/ft_unset.c \
		src/cmd/exec_cmd.c \
		src/cmd/init_cmd.c \
		src/cmd/init_std_cmd.c \
		src/cmd/replace_strs_env.c \
		src/cmd/split_cmd_str.c \
		src/cmd/parse_display.c \
		src/cmd/heredoc.c \
		src/cmd/get_std_cmds.c \
		src/utils/header.c \
		src/utils/strjoin_and_free.c \
		src/utils/utils.c \
		src/utils/free.c \
		src/utils/close_fds.c \
		src/utils/getenv.c
OBJ =	$(SRC:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) $(LFLAGS) -o $@
	@echo "Minishell compiled !"

obj/%.o: src/%.c | obj
	@echo "Compiling: $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	@make -C lib

clean:
	/bin/rm -rf $(OBJ)
	make clean -C lib && make clean -C lib

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIBFT)

re: fclean all
	make fclean -C lib && make clean -C lib

.PHONY: all clean fclean re