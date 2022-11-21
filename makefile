log: compile
	./a.out b > run.log

run: compile
	./a.out

compile:
	gcc src/lib/*.c src/*.c main.c 