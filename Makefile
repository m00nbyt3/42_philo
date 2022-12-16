# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 15:57:18 by ycarro            #+#    #+#              #
#    Updated: 2022/12/16 15:21:24 by ycarro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := gcc

HDIR := include/
INCLUDE :=  -I $(HDIR)
HEADERFILES := include/philo.h

SRCFILES := main.c \
			controller.c \
			lunch.c \
			time.c \
			utils.c

OBJFILES := $(SRCFILES:%.c=obj/%.o)

CFLAGS := -Wall -Wextra -Werror $(INCLUDE)
LFLAGS := -pthread -g3 -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJFILES)
	$(CC) $(OBJFILES) -o $@ #$(LFLAGS)

obj/%.o: src/%.c $(HEADERFILES)
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		rm -f $(OBJFILES)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re