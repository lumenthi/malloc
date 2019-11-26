# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/22 14:06:43 by lumenthi          #+#    #+#              #
#    Updated: 2019/11/26 20:02:52 by lumenthi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re run

HOST = $(HOSTTYPE)
CURRENT_DIR = $(shell pwd)

ifeq ($(HOST),)
	HOST := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOST).so
SYMLINK = libft_malloc.so

LIBPATH = $(CURRENT_DIR)/$(NAME)
SYMLINKPATH = $(CURRENT_DIR)/$(SYMLINK)

CC = gcc
FLAGS = -Wall -Werror -Wextra -fPIC -g

GREEN = '\033[4;32m'
RED = '\033[4;31m'
BLANK = '\033[0m'
YELLOW = '\033[4;33m'
CYAN = '\033[4;38;5;51m'

TICK = '\033[1;32m~\033[0m'
CROSS = '\033[1;31mx\033[0m'

LIBDIR = libft
SRCDIR = sources
HEADDIR = headers
OBJDIR = objs

LIBFT = $(LIBDIR)/libft.a
LIBFT_OBJ = $(LIBDIR)/objs

HEADS = manager.h

SRCS = malloc.c \
				free.c \
				realloc.c \
				show_alloc_mem.c \

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS))
HEADERS = $(addprefix $(HEADDIR)/, $(HEADS))
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

vpath %.c sources

all: $(SYMLINKPATH)

$(SYMLINKPATH): $(NAME)
	@ ln -s -f $(LIBPATH) $(SYMLINKPATH)
	@ printf " %b | Created %b%b%b symlink\n" $(TICK) $(CYAN) $(SYMLINK) $(BLANK)

$(NAME): $(OBJS) ${HEADERS}
	@ make -sC $(LIBDIR)
	@ $(CC) $(OBJS) -shared -o $(NAME) $(LIBFT)
	@ printf " %b | Compiled %b%b%b\n" $(TICK) $(GREEN) $(NAME) $(BLANK)

$(OBJDIR)/%.o: %.c
	@ mkdir -p $(OBJDIR)
	@ $(CC) -c $(FLAGS) -I$(HEADDIR) -I$(LIBDIR) -o $@ $<

clean:
	@ make -sC $(LIBDIR) clean
	@ test -d $(OBJDIR) && \
	rm -rf $(OBJDIR) && \
	printf " %b | " $(TICK) && \
	printf "Removed %b%b%b object folder\n" $(YELLOW) $(NAME) $(BLANK) \
	|| (printf " %b | " $(CROSS) && \
	printf "No %b%b%b object folder\n" $(YELLOW) $(NAME) $(BLANK))

fclean: clean
	@ test -f $(LIBFT) && \
	rm -rf $(LIBFT) && \
	printf " %b | " $(TICK) && \
	printf "Removed %blibft%b library\n" $(RED) $(BLANK) \
	|| (printf " %b | " $(CROSS) && \
	printf "No %blibft%b library\n" $(RED) $(BLANK))
	@ test -f $(NAME) && \
	rm -rf $(NAME) && \
	printf " %b | " $(TICK) && \
	printf "Removed %b%b%b library\n" $(RED) $(NAME) $(BLANK) \
	|| (printf " %b | " $(CROSS) && \
	printf "No %b%b%b library\n" $(RED) $(NAME) $(BLANK))
	@ test -h $(SYMLINK) && \
	rm -f $(SYMLINK) && \
	printf " %b | " $(TICK) && \
	printf "Removed %blibft_malloc.so%b symlink\n" $(CYAN) $(BLANK) \
	|| (printf " %b | " $(CROSS) && \
	printf "No %b%b%b symlink\n" $(CYAN) $(SYMLINK) $(BLANK))

re: fclean all

run: $(SYMLINKPATH)
	@ ./inject ./test || true
