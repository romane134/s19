# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjovanov <bjovanov@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/18 08:32:07 by bjovanov          #+#    #+#              #
#    Updated: 2019/09/14 14:08:07 by rlucas-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs
OBJ_DIR = ./obj
INC_DIR = ./inc

NAME = 21sh

ROOT_FILES = main.c utils.c utils2.c free_tab.c math.c handle_left_redirect.c

BOOTSTRAP_DIR = bootstrap
BOOTSTRAP_FILES = bootstrap.c environment.c handled_token.c set_hash.c set_pwd.c

CLOSE_COMMAND_DIR = close_command
CLOSE_COMMAND_FILES = close_command.c

LEXER_DIR = lexer
LEXER_FILES = lexer.c checker.c order_redirections.c handle_redirections.c

PARSER_DIR = parser
PARSER_FILES = parser.c

EXECUTOR_DIR = exec
EXECUTOR_FILES = exec.c exec_pipe.c exec_semicolon.c exec_command.c \
				expansions/dollar.c expansions/history.c expansions/tilde.c expansions/expansions.c \
				exec_command_clearer.c exec_command_splitter.c exec_command_utils.c \
        exec_redirect.c exec_left_redirect.c exec_redirect_dup.c exec_redirect_utils.c \
         exec_command_utils2.c expansions/utils.c exec_andif.c exec_orif.c exec_command_core.c \
         exec_left_redirect_extends.c exec_jobcontrol.c

TERMCAPS_DIR = termcaps
TERMCAPS_FILES = termcaps_main.c autocompletion.c history.c highlight.c init.c\
					keys.c cut_paste.c edit_line.c move.c autocomplete_file.c\
					autocomplete_fonction.c key2.c key3.c show.c recherche.c\
					autocomplete_command.c autocomplete_var.c

HASH_TABLE_DIR = hash_table
HASH_TABLE_FILE = add_hash.c del_hash.c find_hash.c hash_fonction.c

LINKED_LIST_DIR = linked_list
LINKED_LIST_FILES = print_lists.c close_command/history.c lexer/add_token_item.c\
					lexer/delete_token.c lexer/utils_token_list.c redirect/add_redirect_item.c \
					redirect/delete_redirect.c

BUILTIN_DIR = builtins
BUILTIN_FILES = builtins_utils.c setenv.c unsetenv.c echo.c env.c cd.c env_add_item.c env_error.c \
				env_utils.c exit.c cd_link.c cd_error.c hash.c fc.c fc_option_l.c fc_option.c fc_utils.c

SRC_FILES = $(ROOT_FILES)
SRC_FILES += $(addprefix $(BOOTSTRAP_DIR)/, $(BOOTSTRAP_FILES))
SRC_FILES += $(addprefix $(LEXER_DIR)/, $(LEXER_FILES))
SRC_FILES += $(addprefix $(CLOSE_COMMAND_DIR)/, $(CLOSE_COMMAND_FILES))
SRC_FILES += $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
SRC_FILES += $(addprefix $(EXECUTOR_DIR)/, $(EXECUTOR_FILES))
SRC_FILES += $(addprefix $(TERMCAPS_DIR)/, $(TERMCAPS_FILES))
SRC_FILES += $(addprefix $(LINKED_LIST_DIR)/, $(LINKED_LIST_FILES))
SRC_FILES += $(addprefix $(HASH_TABLE_DIR)/, $(HASH_TABLE_FILE))
SRC_FILES += $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES))

SRC  = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ  = $(addprefix $(OBJ_DIR)/, $(subst .c,.o, $(SRC_FILES)))

CC = gcc #-fsanitize=address
CFLAGS = -Wall -Wextra -Werror

LIB = -L libft/ -lft
LIBFT_INC = libft/includes

KNRM = "\x1B[0m"
KGRN = "\x1B[1;32m"

.PHONY: all clean fclean re

all:
	#@mkdir -p $(OBJ_DIR)
	@make -C libft/
	@make $(NAME)

$(NAME): $(OBJ)
	@echo "Creation de l'executable..."
	@$(CC) $(CLFAGS) $(OBJ) $(LIB) -lncurses -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilation du fichier "$(KGRN)$(notdir $(subst .c,,$<))$(KNRM)
	@mkdir -p $(dir $@) && $(CC) $(CFLAGS) -I $(LIBFT_INC) -I $(INC_DIR) -o $@ -c $<

clean:
	@make clean -C libft/
	@rm -rf $(OBJ_DIR)

fclean:
	@make fclean -C libft/
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)

re: fclean all
