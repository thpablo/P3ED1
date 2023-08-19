all: main.o maze.o tree.o levels.o
	@gcc main.o maze.o tree.o levels.o -o exe

main.o: main.c
	@gcc -c main.c -Wall

maze.o: maze.c
	@gcc -c maze.c -Wall

tree.o: tree.c
	@gcc -c tree.c -Wall

levels.o: levels.c
	@gcc -c levels.c -Wall

run:
	@./exe
