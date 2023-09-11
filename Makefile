SOURCE_FILES = src/draw.c src/heroes.c src/input.c src/main.c src/globals.c src/map.c
FLAGS = -lSDL2_image -Wall -Wextra

game: $(SOURCE_FILES)
	cc $(SOURCE_FILES) $(FLAGS) `sdl2-config --cflags --libs` -o bin/Game 

clean:
	rm -f Game
