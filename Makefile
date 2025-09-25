all:
	gcc snake.c player.c Menu.c -o snake -lSDL2 -lSDL2_ttf && ./snake