all: as6

as6: as6.c
	gcc -pedantic -Wall -Wextra -Werror as6.c
