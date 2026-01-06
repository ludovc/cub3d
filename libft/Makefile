NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../inc
OBJDIR = obj

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_get_next_line.c ft_isalnum.c \
	   ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isnum.c ft_isprint.c \
	   ft_itoa.c ft_lstadd_back.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
	   ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c \
	   ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_printf.c \
	   ft_putchar_fd.c ft_putchar_pf.c ft_putendl_fd.c ft_puthexnbr_pf.c \
	   ft_putnbr_fd.c ft_putnbr_pf.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	   ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	   ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	   ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
