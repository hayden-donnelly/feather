all:
	gcc main.c engine.c modules/utils.c modules/camera.c modules/sprite.c modules/box_collider.c modules/tilemap.c modules/transform.c input.c game.c -o play.app -lsdl2 -lSDL2_Image