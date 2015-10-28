all: as6

as6: as6.c functions.c
	gcc -pedantic -Wall -Wextra -Werror as6.c functions.c nacl/lib/amd64/libnacl.a base64.c -o as6

test: tests.c functions.c
	gcc -g tests.c functions.c nacl/lib/amd64/libnacl.a base64.c -o test
