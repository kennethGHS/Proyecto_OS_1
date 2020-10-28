.PHONY: clean
CC = gcc
APP = interface
SRC = $(APP).c
CFLAGS = $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 gtk+-3.0 --libs --cflags )
PT = -pthread
DEPS1 = ../BasicStructures/process_structure
DEPS2 = ../ThreadManagement/process_admin
DEPS3 = ../BasicStructures/interval_structure
includes = $(wildcard DEPS)


$(APP):$(SRC) $(DEPS1).h $(DEPS2).h $(DEPS3).h
		$(CC) -o $(APP) $(SRC) $(DEPS1).c $(DEPS2).c $(DEPS3).c -I$(DEPS1) -I$(DEPS2) -I$(DEPS3) $(CFLAGS) $(PT)
clean:
		rm $(APP)
