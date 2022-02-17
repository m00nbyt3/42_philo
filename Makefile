# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 13:14:44 by ycarro            #+#    #+#              #
#    Updated: 2022/02/17 13:03:33 by ycarro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 12:26:21 by ycarro            #+#    #+#              #
#    Updated: 2022/01/13 15:48:52 by ycarro           ###   ########.fr        #
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