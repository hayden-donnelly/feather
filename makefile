EXEC		= game
CC			= gcc
EXTENSION	= c
SRCS_DIR	= src

LFLAGS		+= -lm -lSDL2 -lSDL2_image
SRCS		= $(shell find $(SRCS_DIR) -type f -name *.$(EXTENSION))

all:
	$(CC) $(SRCS) -o $(EXEC) $(LFLAGS)

run:
	./$(EXEC)
