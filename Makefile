# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 09:24:12 by ksura             #+#    #+#              #
#    Updated: 2022/11/03 10:07:52 by ksura            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philosophers
CC = gcc -fsanitize=thread -g
CFLAGS := -Wall -Werror -Wextra
HEADER = ./header
SRCDIR = src/
OBJDIR = build/


SRC := main.c timing.c init.c philos.c

GREEN = \033[0;32m
RED = \033[0;31m

OBJS = ${SRC:.c=.o}

OBJECTS_PREF := $(addprefix $(OBJDIR), $(OBJS))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS_PREF) $(OBJDIR)
	@$(CC) $(FLAGS) $(OBJECTS_PREF) -I$(HEADER) -o $@
	@echo "$(GREEN)$(NAME) was created"

$(OBJECTS_PREF): build/%.o : src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER) $(INCLUDES)
	
$(OBJECTS_PREF_BO): $(OBJDIR_BO)%.o : bonus/%.c
	@mkdir -p $(OBJDIR_BO)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER) $(INCLUDES)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) was deleted"

re: fclean all

debug: $(OBJECTS_PREF) $(OBJDIR)
	$(CC) $(FLAGS) $(OBJECTS_PREF) $(LIBRARIES) -I$(HEADER) -o $(NAME) -g