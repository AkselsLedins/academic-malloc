##
## Makefile for Malloc
##
## Made by ledins_a
## Login   <aksels.ledins@gmail.com>
##
## Started on  Sun Feb 16 19:23:15 2014 ledins_a
## Last update Sun Feb 16 19:23:17 2014 ledins_a
##

LIBNAME = libmy_malloc_$(HOSTTYPE).so
LINK = libmy_malloc.so

CC = gcc


SRC = 	malloc.c \
		free.c \
		realloc.c \
		calloc.c \
		builtins.c


CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(LIBNAME)

#compilation
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) -fpic -pthread


#linkage
$(LIBNAME): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -shared
	ln -s $(LIBNAME) $(LINK)

clean:
	$(RM) $(OBJ)


fclean: clean
	$(RM) $(LIBNAME)
	$(RM) $(LINK)

re: fclean all
