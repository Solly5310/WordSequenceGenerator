final : words.o Graph.o
	gcc -o words words.o Graph.o

words.o : words.c
	gcc -Wall -Werror -std=c11 -c words.c

Graph.o : Graph.c
	gcc -Wall -Werror -std=c11 -c Graph.c