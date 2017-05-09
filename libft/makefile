# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/21 16:11:06 by dhuang            #+#    #+#              #
#    Updated: 2017/01/05 21:46:56 by dhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all testing clean fclean re

CC := gcc

CFLAGS := -Wall -Werror -Wextra

vpath %.h includes

INCLUDES := -I includes/libft.h -I includes/get_next_line.h

#Printing things
SRCS := ft_putchar.c ft_putstr.c ft_putnbr.c ft_putendl.c ft_putnbrnl.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \

#ASCII things
SRCS += ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_islower.c ft_isupper.c ft_toupper.c ft_tolower.c \

#String things
SRCS += ft_strequ.c ft_strnequ.c \
	ft_strcmp.c ft_strncmp.c \
	ft_strcpy.c ft_strncpy.c \
	ft_strchr.c ft_strrchr.c \
	ft_strcat.c ft_strncat.c ft_strlcat.c \
	ft_strstr.c ft_strnstr.c \
	ft_strlen.c ft_strrev.c  ft_swap.c \

#Memory things and more complicated string things
SRCS += ft_bzero.c ft_memset.c ft_strclr.c \
	ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	ft_strdup.c ft_memalloc.c ft_memdel.c \
	ft_strnew.c ft_strdel.c ft_strjoin.c ft_strjoinreplace.c \
	ft_strsub.c ft_strtrim.c ft_strsplit.c ft_striter.c ft_striteri.c \
	ft_strmap.c ft_strmapi.c \

#List things
SRCS += ft_lstnew.c ft_lstadd.c ft_lstiter.c \
	ft_lstdelone.c ft_lstdel.c ft_lstmap.c \
	ft_mrlc.c ft_srlc.c ft_strnew2.c \
	get_next_line.c \
	ft_lstaddend.c ft_lstmemdel.c

#Math things
SRCS += ft_atoi.c ft_atoibase.c \
	ft_itoa.c ft_itoabase.c \
	ft_max.c ft_min.c ft_maxmap.c ft_minmap.c \

OBJDIR := obj

OBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(SRCS)))

NAME := libft.a

$(OBJDIR)/%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo 'Done creating $@...'

all: $(NAME)

$(NAME): libft.h get_next_line.h $(OBJS)
		@echo  "Creating library..."
		@ar rc $(NAME) $(OBJS)
		@echo "Indexing library..."
		@ranlib $(NAME)
		@echo "All done!"

$(OBJS): libft.h get_next_line.h $(SRCS) | $(OBJDIR)

$(OBJDIR):
		@echo "Creating subdirectory for object files..."
		@mkdir $(OBJDIR)

clean:
		@echo "Deleting object files and subdirectory..."
		@rm -f $(OBJS)
		@rm -rf $(OBJDIR)

fclean: clean
		@echo "Deleting libft.a..."
		@rm -f $(NAME)

re: fclean all
