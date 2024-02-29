OBJCS		:=	sources/main.o \
				sources/signals/AV_signals.o \
				sources/builtins/JG_builtins.o \
				sources/builtins/JG_env.o \
				sources/builtins/JG_pwd.o \
				sources/builtins/JG_echo.o \
				sources/builtins/JG_cd.o \
				sources/builtins/JG_exit.o \
				sources/builtins/JG_export.o \
				sources/builtins/JG_exec.o \

LIBFT_A		:=	libft/libft.a
INCLUDES	:=	includes/minishell.h
NAME		:=	minishell

CFLAGS		:=	-Wall -Wextra -Werror
READL		:=	-L/usr/local/lib -I/usr/local/include -lreadline -L $(shell brew --prefix readline)/lib -I $(shell brew --prefix readline)/include

all			:	libgen $(INCLUDES) $(NAME)

$(NAME)		:	$(INCLUDES) $(OBJCS)
	${CC} ${CFLAGS} $(OBJCS) $(LIBFT_A) $(READL) -o ${NAME}

%.o			:	%.c
	$(CC) -c $(CFLAGS) -o $@ $^

libgen		:
	@make -C libft

clean		:
	@rm -f $(OBJCS)
	@make clean -C libft

fclean		:	clean
	@rm -f $(NAME)
	@make fclean -C libft

re			:	fclean all

.PHONY		:	all clean fclean re libgen
