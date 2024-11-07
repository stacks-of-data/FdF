CFLAGS = -Wall -Wextra -Werror
SRCS = fdf.c map_utils.c map_utils2.c utils.c utils2.c math_utils.c draw_utils.c draw_utils2.c hooks.c hooks_utils.c
SRCS := $(addprefix srcs/,$(SRCS))
OBJS = $(SRCS:.c=.o)
NAME = fdf
LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)
$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -L./libft -lft -lmlx -lXext -lX11 -lm -o $(NAME)
$(LIBFT):
	$(MAKE) -C libft
clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
re: fclean all
.PHONY: all clean fclean re
