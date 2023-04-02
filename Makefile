NAME = bsq
SRCS = $(wildcard *.c)
HEADER = header.h
CFLAGS = #-Wall -Wextra -Werror

all:
	gcc $(CFLAGS) $(SRCS) $(HEADER) -o $(NAME) 

clean:
	rm -f $(NAME)
	rm -f 

debug:
	gcc $(CFLAGS) -g $(SRCS) $(HEADER) -o $(NAME)

.PHONY:	all clean fclean debug




