all: main.o maze.o tree.o
	@gcc main.o maze.o tree.o -o exe

main.o: main.c
	@gcc -c main.c -Wall

maze.o: maze.c
	@gcc -c maze.c -Wall

tree.o: tree.c
	@gcc -c tree.c -Wall

run:
	@./exe
