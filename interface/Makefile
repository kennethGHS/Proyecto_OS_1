.PHONY: clean
CC = gcc
APP = interface
SRC = $(APP).c
CFLAGS = $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 gtk+-3.0 --libs --cflags)

$(APP):$(SRC)
		$(CC) -o $(APP) $(SRC) $(CFLAGS) 
clean:
		rm $(APP)
