# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 18:25:23 by ffoissey          #+#    #+#              #
#    Updated: 2019/02/05 11:37:19 by ffoissey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FILE = ls list mergesort_lst args tool file format_file stat process_ls		   \
	   mode_ls printls printls_normal
LIB = libft/libft.a
SRCS = $(patsubst %,srcs/ft_%.c,$(FILE))
OBJS = $(patsubst %,ft_%.o,$(FILE))
INCLUDES += -I includes/
INCLUDES += -I libft/includes
INCLUDES += -I libft/includes/get_next_line
INCLUDES += -I libft/includes/ft_printf
HEAD = includes/ls.h
CFLAGS = -Wall -Werror -Wextra
CC = clang

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(INCLUDES) -o $@

%.o: srcs/%.c $(HEAD) $(LIB)
	$(CC) $(CFLAGS) -c $< $(INCLUDES)

$(LIB):
	make -C libft/

clean:
	make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
