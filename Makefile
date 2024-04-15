build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o renderer

run:build
	./renderer

clean:
	rm renderer

mkr:run