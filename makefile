all:
	gcc main.c engine.c components.c input.c game.c -o play.app -lsdl2 -lSDL2_Image