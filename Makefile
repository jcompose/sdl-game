SOURCE_FILES = main.c

game: $(SOURCE_FILES)
	cc $(SOURCE_FILES) `sdl2-config --cflags --libs` -o Game

clean:
	rm -f Game
