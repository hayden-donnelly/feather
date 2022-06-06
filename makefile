EXEC		= game
CC			= gcc
EXTENSION	= c
SRCS_DIR	= src

LFLAGS		+= -lm -lsdl2 -lsdl2_image -lsdl2_ttf
SRCS		= $(shell find $(SRCS_DIR) -type f -name *.$(EXTENSION))

all:
	$(CC) $(SRCS) -o $(EXEC) $(LFLAGS)

run:
	./$(EXEC)