CC:=cc
CFLAGS:= -Wall -Wextra -Werror
SRCS:= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c\
	   ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c\
	   ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
	   ft_strcmp.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
	   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
	   ft_putendl_fd.c ft_putnbr_fd.c ft_memchr.c 


OBJS:= $(SRCS:.c=.o)
BONUS:= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
        ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJSB:= $(BONUS:.c=.o)

HEADER:= libft.h

NAME:= libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)	

bonus: $(OBJSB)
	ar rcs $(NAME) $(OBJSB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJSB)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus