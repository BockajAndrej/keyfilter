CFLAGS=-std=c11 -Wall -Wextra -Werror

keyfilter: keyfilter.c
	gcc $(CFLAGS) keyfilter.c -o keyfilter