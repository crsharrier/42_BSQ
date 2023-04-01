NAME = bsq
SRCS = $(wildcard *.c)
HEADER = header.h
CFLAGS = #-Wall -Wextra -Werror

all:
	gcc $(CFLAGS) $(SRCS) $(HEADER) -o $(NAME) 

clean:
	rm -f $(NAME)

debug:
	all -g

.PHONY:	all clean fclean debug




