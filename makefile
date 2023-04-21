SRC		=	main.c

CC		=	gcc

CFLAGS	=	-Werror -Wextra -Wall

all :
	$(CC) $(CFLAGS) $(SRC)
	./a.out
