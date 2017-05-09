# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/05 21:53:35 by dhuang            #+#    #+#              #
#    Updated: 2017/01/11 16:20:02 by dhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re testing

vpath %.h includes

CC = gcc

CFLAGS = -Wall -Werror -Wextra

CTFLAGS = -fsanitize=address

INCLUDES = -I includes/

SRCFILES = 	ft_printf.c \
			datasetup.c \
			datasetup2.c \
			parseswitch.c \
			formatnum.c \
			ft_dtoa.c \
			insertformat.c \
			padcs.c \
			padnum.c \
			padswitch.c \
			parsedbl.c \
			parsenum.c \
			parsestr.c \
			parseunum.c \
			parsezjt.c \
			formatdbl.c \
			formatedbl.c \
			padhex.c \
			padoct.c \

SRCDIR := srcs/

SRC:= $(addprefix $(SRCDIR), SRCFILES))

#Printing things
LIBSRCS :=	ft_putchar.c \
			ft_putstr.c \
			ft_putnbr.c \
			ft_putendl.c \
			ft_putnbrnl.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_putendl_fd.c \

#ASCII things
LIBSRCS += 	ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_islower.c \
			ft_isupper.c \
			ft_toupper.c \
			ft_tolower.c \

#String things
LIBSRCS += 	ft_strequ.c \
			ft_strnequ.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strlen.c \
			ft_strrev.c \
			ft_swap.c \
			ft_wstrdup.c \
			ft_wstrcpy.c \
			ft_strjoinreplace.c \
			ft_wctouni.c \

#Memory things and more complicated string things
LIBSRCS += 	ft_bzero.c \
			ft_memset.c \
			ft_strclr.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strdup.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strjoin.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \

#Math things
LIBSRCS += 	ft_atoi.c \
			ft_atoibase.c \
			ft_itoa.c \
			ft_itoabase.c \
			ft_max.c \
			ft_min.c \
			ft_maxmap.c \
			ft_minmap.c \

LIBFTDIR := ../libft

LIBSRC:= $(addprefix $(LIBFTDIR)/, LIBSRCS))

OBJDIR := obj

LOBJDIR := ../libft/obj

OBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(SRCFILES)))

LOBJS := $(addprefix $(LOBJDIR)/, $(patsubst %.c,%.o,$(LIBSRCS)))

NAME = libftprintf.a

all: $(NAME)

$(LOBJS): $(LSRCS) | $(LOBJDIR)

$(OBJS): ft_printf.h $(SRCS) | $(OBJDIR)

$(LOBJDIR)/%.o : $(LIBFTDIR)/%.c
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo "Done creating $@..."

$(LOBJDIR): | $(OBJDIR)
		@echo "Creating subdirectory libft object files..."
		@mkdir $(LOBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo "Done creating $@..."

$(OBJDIR):
		@echo "Creating subdirectory for object files..."
		@mkdir $(OBJDIR)

$(NAME): ft_printf.h $(LOBJS) $(OBJS)
		@echo "Creating printf library..."
		@ar rc $(NAME) $(OBJS) $(LOBJS)
		@echo "Indexing printf library..."
		@ranlib $(NAME)
		@echo "All done!"

#Debugging option with address sanitizer
myasan: ft_printf.h $(OBJS) $(NAME) main.c
		@echo "Creating myasan..."
		@$(CC) $(LDFLAGS) $(CTFLAGS) $(GFLAGS) main.c -o $@ -L ./ -lftprintf
		@echo "All done!"

clean:
		@echo "Deleting printf object files and subdirectory..."
		@rm -f $(LOBJS)
		@rm -rf $(LOBJDIR)
		@rm -f $(OBJS)
		@rm -rf $(OBJDIR)

fclean: clean
		@echo "Deleting $(NAME)..."
		@rm -rf $(NAME)
		@rm -rf myasan

re: fclean all
