# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 11:21:00 by gdelvign          #+#    #+#              #
#    Updated: 2024/06/02 18:35:52 by jgasparo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 							Name of the executable							   #
# **************************************************************************** #

NAME			:= minishell

# **************************************************************************** #
# 								  File paths								   #
# **************************************************************************** #

LIBFT_BUILD 	:= ./libft/.build/
LIBFT_DIR		:= ./libft/
INC_DIR 		:= ./includes/
SRC_DIR			:= ./sources/
BUILD_DIR  		:= ./.build/

# **************************************************************************** #
# 							  Librairies needed								   #
# **************************************************************************** #

LIBFT 			:= libft.a

# **************************************************************************** #
# 							  	Source files								   #
# **************************************************************************** #

SRC_FILES			:= main
UTILS_SRC			:= error error2 utils utils2 clean clean2 history
SIGNALS_SRC			:= signals
BUILTINS_SRC		:= builtins env pwd echo cd exit export unset
BUILTINS_UTILS_SRC	:= exit_utils exit_utils2 export_utils export_utils2 \
					export_utils3 export_utils4 export_utils5 cd_utils \
					cd_utils2 cd_utils3
LEXER_SRC			:= lexer
LEXER_UTILS_SRC 	:= lexer_utils lexer_utils2 lexer_utils3
PARSER_UTILS_SRC	:= parser_utils parser_utils2 parser_utils3 parser_utils4
PARSER_SRC			:= parser
EXPAND_SRC			:= expander
EXPAND_UTILS_SRC	:= expander_utils expander_utils2 expander_utils3 \
					expander_utils4 expander_utils5
EXEC_SRC			:= executor
EXEC_UTILS_SRC		:= executor_utils executor_utils2 executor_utils3 \
					executor_utils4 executor_utils5 
HEREDOC_SRC			:= heredoc heredoc_utils

SRC				:= $(addprefix $(SRC_DIR),$(addsuffix .c, $(SRC_FILES)))
SRC 			+= $(addprefix $(SRC_DIR)builtins/, $(addsuffix .c, $(BUILTINS_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)signals/, $(addsuffix .c, $(SIGNALS_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)lexer/, $(addsuffix .c, $(LEXER_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)utils/, $(addsuffix .c, $(UTILS_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)parser/, $(addsuffix .c, $(PARSER_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)expander/, $(addsuffix .c, $(EXPAND_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)executor/, $(addsuffix .c, $(EXEC_SRC)))
SRC				+= $(addprefix $(SRC_DIR)lexer/lexer_utils/, $(addsuffix .c, $(LEXER_UTILS_SRC)))
SRC				+= $(addprefix $(SRC_DIR)parser/parser_utils/, $(addsuffix .c, $(PARSER_UTILS_SRC)))
SRC				+= $(addprefix $(SRC_DIR)expander/expander_utils/, $(addsuffix .c, $(EXPAND_UTILS_SRC)))
SRC				+= $(addprefix $(SRC_DIR)executor/executor_utils/, $(addsuffix .c, $(EXEC_UTILS_SRC)))
SRC				+= $(addprefix $(SRC_DIR)builtins/builtins_utils/, $(addsuffix .c, $(BUILTINS_UTILS_SRC)))
SRC				+= $(addprefix $(SRC_DIR)heredoc/, $(addsuffix .c, $(HEREDOC_SRC)))


# **************************************************************************** #
# 							  	Object files								   #
# **************************************************************************** #

OBJS 			:= $(SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)
DEPS        	:= $(OBJS:.o=.d)

# **************************************************************************** #
# 							  Compilation flags								   #
# **************************************************************************** #

CC 				:= cc -g -O0
CFLAGS 			:= -Wall -Wextra -Werror
CPPFLAGS		:= -MMD -MP
READL			:=	-L/usr/local/lib -I/usr/local/include -lreadline \
					-L $(shell brew --prefix readline)/lib \
					-I $(shell brew --prefix readline)/include
DEBUG			:= #-fsanitize=address

# **************************************************************************** #
# 							  	   Colors	    							   #
# **************************************************************************** #

GREEN 			= \033[0;32m
CYAN 			= \033[36;1m
YELLOW			= \033[33;1m
WHITE 			= \033[0m

# **************************************************************************** #
# 							  	   Rules	    							   #
# **************************************************************************** #


all : $(NAME)

-include $(DEPS)
$(BUILD_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -I $(INC_DIR)

$(LIBFT_BUILD)$(LIBFT):
	@echo "\n$(CYAN)Generating Libft...$(WHITE)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft created!$(WHITE)\n"

$(NAME): $(OBJS) $(LIBFT_BUILD)$(LIBFT)
	@echo "${CYAN}Generating minishell.${WHITE}"
	@$(CC) $(DEBUG) $(CFLAGS) $(OBJS) $(LIBFT_BUILD)$(LIBFT) $(READL) -o $(NAME)
	@echo "${GREEN}Compilation successful !${WHITE}"


clean :
	@echo "\n${CYAN}Deleting object files...${WHITE}"
	@$(RM) -r $(BUILD_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(GREEN)Object files were deleted.$(WHITE)\n"
	
fclean : clean
	@echo "$(CYAN)Cleaning all...$(WHITE)\n"
	@make fclean -C $(LIBFT_DIR)
	@echo "$(GREEN)$(LIBFT) was deleted.$(WHITE)"
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) was deleted.$(WHITE)"

re : fclean all

.PHONY : all clean fclean re
