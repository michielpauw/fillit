# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dolivier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 13:30:10 by dolivier          #+#    #+#              #
#    Updated: 2017/11/27 10:31:23 by mpauw            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FLAGS = -Wall -Wextra -Werror 
INCLUDES = fillit.h
SRCS = read.c \
   checks.c \
   fillit.c \
   solve.c \
   setup_map.c
OBJ = $(SRCS:%.c=%.o)
LIBDIR = libft/
LIBFT = libft.a
MAKE = make
all : $(NAME)

$(NAME): $(OBJ) $(LIBDIR)$(LIBFT)
	-@gcc $(FLAGS) -o $(NAME) $(OBJ) -I$(LIBDIR) -L $(LIBDIR) -lft
	-@echo "Fillit ready"

%.o: %.c $(INCLUDES)
	-@gcc $(FLAGS) -I$(LIBDIR) -c $(SRCS)

$(LIBDIR)$(LIBFT):
	$(MAKE) -C $(LIBDIR) $(LIBFT)

clean:
	$(MAKE) -C  $(LIBDIR) clean
	/bin/rm -rf .h.gch
	/bin/rm -rf *.o

fclean: clean
	$(MAKE) -C $(LIBDIR) fclean
	/bin/rm -f $(NAME)

re: fclean all
