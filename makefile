EXEC		= game.app
CC			= gcc
EXTENSION	= c
SRCS_DIR	= src

LFLAGS		+= -lm -lsdl2 -lSDL2_Image
SRCS		= $(shell find $(SRCS_DIR) -type f -name *.$(EXTENSION))

all:
	CC $(SRCS) -o $(EXEC) $(LFLAGS)

run:
	./$(EXEC)