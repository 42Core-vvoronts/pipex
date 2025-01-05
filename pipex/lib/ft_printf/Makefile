# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 19:28:02 by vvoronts          #+#    #+#              #
#    Updated: 2025/01/05 14:23:13 by vvoronts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a

SRCS := ft_printf.c
OBJS := $(SRCS:.c=.o)
DEPS := ft_printf.h

AR := ar -rcs
CFLAGS := -Wall -Wextra -Werror

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

$(OBJS): $(SRCS) $(DEPS)
	@$(CC) $(CFLAGS) -c $(SRCS)

a: all
	@echo "Building $(NAME) ..."

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re