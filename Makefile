# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/03 12:00:00 by emheuga           #+#    #+#              #
#    Updated: 2026/04/04 14:07:06 by emheuga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER      = server
CLIENT      = client
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

PRINTF_DIR  = ft_printf
PRINTF_LIB  = $(PRINTF_DIR)/libftprintf.a
PRINTF_FLAG = -L$(PRINTF_DIR) -lftprintf
INCLUDES    = -I$(PRINTF_DIR)

SERVER_SRCS = server.c
CLIENT_SRCS = client.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

all: $(PRINTF_LIB) $(SERVER) $(CLIENT)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF_DIR)

$(SERVER): $(SERVER_OBJS) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(PRINTF_FLAG) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJS) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(PRINTF_FLAG) -o $(CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(PRINTF_DIR) clean
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
