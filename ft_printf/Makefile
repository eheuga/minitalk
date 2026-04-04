# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 15:00:22 by emheuga           #+#    #+#              #
#    Updated: 2025/11/11 17:25:45 by emheuga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= ft_printf.c ft_putchar.c ft_puthexa.c ft_putnbr.c ft_putstr.c \
				  ft_putunsigned.c ft_type.c ft_putptr.c

OBJS			= $(SRCS:.c=.o)
CC				= cc
CFLAGS			= -Werror -Wextra -Wall
RM				= rm -f
NAME			= libftprintf.a

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
