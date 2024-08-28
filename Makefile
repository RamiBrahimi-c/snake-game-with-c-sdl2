all:
	gcc -I src/include -L src/lib -o snake snake.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf