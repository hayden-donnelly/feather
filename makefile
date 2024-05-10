EXEC = game
CC = gcc
EXTENSION = c
SRCS_DIR = src
BUILD_DIR = build

LFLAGS += -lm `sdl2-config --cflags --libs` -lSDL2_image
SRCS = $(shell find $(SRCS_DIR) -type f -name *.$(EXTENSION))

all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRCS) -o $@ $(LFLAGS)

run: $(BUILD_DIR)/$(EXEC)
	./$(BUILD_DIR)/$(EXEC)

clean:
	rm -rf $(BUILD_DIR)
