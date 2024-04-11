# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdelvign <gdelvign@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 11:21:00 by gdelvign          #+#    #+#              #
#    Updated: 2024/04/11 13:12:26 by gdelvign         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 							Name of the executable							   #
# **************************************************************************** #

NAME			:= minishell

# **************************************************************************** #
# 								  File paths								   #
# **************************************************************************** #

LIBFT_DIR 		:= ./libft/
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

SRC_FILES		:= main
SIGNALS_SRC		:= signals
BUILTINS_SRC	:= builtins env pwd echo cd exit export exec
LEXER_SRC		:= lexer
UTILS_SRC		:= error utils lexer_utils lexer_utils2 lexer_utils3 parser_utils \
parser_utils2 parser_utils3 clean export_utils export_utils2 expander_utils \
expander_utils2 expander_utils3 history
PARSER_SRC		:= parser
EXPAND_SRC		:= expander

SRC				:= $(addprefix $(SRC_DIR),$(addsuffix .c, $(SRC_FILES)))
SRC 			+= $(addprefix $(SRC_DIR)builtins/, $(addsuffix .c, $(BUILTINS_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)signals/, $(addsuffix .c, $(SIGNALS_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)lexer/, $(addsuffix .c, $(LEXER_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)utils/, $(addsuffix .c, $(UTILS_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)parser/, $(addsuffix .c, $(PARSER_SRC)))
SRC 			+= $(addprefix $(SRC_DIR)expander/, $(addsuffix .c, $(EXPAND_SRC)))

# **************************************************************************** #
# 							  	Object files								   #
# **************************************************************************** #

OBJS 			:= $(SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)
DEPS        	:= $(OBJS:.o=.d)

# **************************************************************************** #
# 							  Compilation flags								   #
# **************************************************************************** #

CC 				:= cc
CFLAGS 			:= -Wall -Wextra -Werror
CPPFLAGS		:= -MMD -MP
READL			:=	-L/usr/local/lib -I/usr/local/include -lreadline \
					-L $(shell brew --prefix readline)/lib -I $(shell brew --prefix readline)/include
DEBUG			:= -O0 -g -fsanitize=address

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

$(NAME): $(OBJS) $(LIBFT_DIR)$(LIBFT)
	@echo "${CYAN}Generating project executable.${WHITE}"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) $(READL) $(DEBUG) -o $(NAME)
	@echo "${GREEN}Compilation successful !${WHITE}"
	@./$(NAME)

$(LIBFT_DIR)$(LIBFT):
	@echo "\n$(CYAN)Generating Libft...$(WHITE)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft created!$(WHITE)\n"

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
