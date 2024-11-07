# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geibo <geibo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 06:55:38 by codespace         #+#    #+#              #
#    Updated: 2024/11/08 01:32:57 by geibo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -w -O2 #-fsanitize=address
INCLUDES = -Iincludes

# Source files
SRCS_DIR = src
MAIN_DIR = main
UTILS_DIR = utils
LIBFT_DIR = libft
PHILO_UTIL = philo_util
SRCS_FILES = $(addprefix $(MAIN_DIR)/, main.c) \
			 $(addprefix $(UTILS_DIR)/, arg_check.c free.c init.c init_utils.c print_status.c time.c init_philos.c init_sitting.c) \
			 $(addprefix $(LIBFT_DIR)/, ft_atoi.c ft_strcmp.c) \
			 $(addprefix $(PHILO_UTIL)/, fork.c handle_eat.c handle_sleep.c manage_threads.c monitor_threads.c philo_routine.c)

SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))

# Object files
OBJS_DIR = objs
OBJS_DIRS = $(OBJS_DIR) $(OBJS_DIR)/$(MAIN_DIR) $(OBJS_DIR)/$(UTILS_DIR) $(OBJS_DIR)/$(LIBFT_DIR) $(OBJS_DIR)/$(PHILO_UTIL)
OBJS_FILES = $(patsubst %.c,%.o,$(SRCS_FILES))
OBJS = $(addprefix $(OBJS_DIR)/,$(OBJS_FILES))

# Binary
NAME = philo

# Colors and text formatting
RESET = \033[0m
BOLD = \033[1m
DIM = \033[2m
UNDERLINE = \033[4m
BLINK = \033[5m
INVERT = \033[7m
LIGHT_BLUE = \033[94m
YELLOW = \033[93m

# Makefile rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BOLD)$(LIGHT_BLUE)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "$(BOLD)$(LIGHT_BLUE)$(NAME) created successfully!$(RESET)"
	@echo "$(BOLD) $(YELLOW)Run with ./$(NAME)$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIRS)
	@echo "$(BOLD)$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning objects...$(RESET)"
	@rm -rf $(OBJS_DIR)
	@rm -f a.out

fclean: clean
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
