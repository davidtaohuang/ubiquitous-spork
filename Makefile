# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/21 16:11:06 by dhuang            #+#    #+#              #
#    Updated: 2016/11/02 21:14:29 by dhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re testing

vpath %.h includes

CC = gcc

CFLAGS = -Wall -Werror -Wextra 

ASAN = -fsanitize=address

GFLAGS = -framework OpenGL -framework AppKit

INCLUDES = -I includes/

SRCFILES = 	main.c \
			ft_redraw.c \
			ft_thread.c \
			clean.c \
			parsemap.c \
			ft_khooks.c \
			textures.c \
			floorceiling.c \

SRCDIR := srcs

SRC:= $(addprefix $(SRCDIR)/, SRCFILES))

LFT = libft/libft.a

LFTPRINTF = ft_printf/libftprintf.a

MINILIB = minilibx_macos/libmlx.a

OBJDIR := obj

OBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(SRCFILES)))

NAME = wolf3d

all: $(NAME)

$(LFT):
		make -C libft/

$(LFTPRINTF):
		make -C ft_printf/

$(MINILIB):
		@echo "Creating $@..."
		@make -C minilibx_macos/
		@echo "Done creating $@!"

$(OBJS): wolf3d.h $(SRCS) | $(OBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo "Done creating $@..."

$(OBJDIR):
		@echo "Creating subdirectory for object files..."
		@mkdir $(OBJDIR)

$(NAME): $(OBJS) $(LFT) $(LFTPRINTF) $(MINILIB)
		@echo "Creating $(NAME)..."
		@$(CC) $(CFLAGS) $(GFLAGS) $(OBJS) -o $@ -L minilibx_macos/ -lmlx -L libft/ -lft -L ft_printf/ -lftprintf
		@echo "All done!"

clean:
		@echo "Deleting fractol object files and subdirectory..."
		@rm -f $(OBJS)
		@rm -rf $(OBJDIR)
		make clean -C libft/
		make clean -C ft_printf/

fclean: clean
		@echo "Deleting $(NAME)..."
		@rm -f $(NAME)
		make fclean -C libft/
		make fclean -C ft_printf/
		@make clean -C minilibx_macos/

re: fclean all
