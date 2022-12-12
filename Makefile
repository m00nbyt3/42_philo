# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 15:57:18 by ycarro            #+#    #+#              #
#    Updated: 2022/10/26 15:57:29 by ycarro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := gcc

HDIR := include/
INCLUDE :=  -I $(HDIR)
HEADERFILES := include/philo.h

SRCFILES := main.c \
			controller.c \
			launch.c \
			time.c \
			utils.c

OBJFILES := $(SRCFILES:%.c=obj/%.o)

CFLAGS := -Wall -Wextra -Werror $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJFILES)
	$(CC) $(OBJFILES) -o $@

obj/%.o: src/%.c $(HEADERFILES)
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		rm -f $(OBJFILES)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re