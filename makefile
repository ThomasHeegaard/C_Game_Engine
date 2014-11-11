CC=gcc
CFLAGS= -g -Wall
LDFLAGS= -lm -lSDL2
SOURCES= source/utils/sdl_wrapper.c source/utils/list.c source/graphics/fps_manager.c source/graphics/sprite.c source/graphics/graphics.c source/engine/entity.c source/engine/test_entity.c source/engine/ship_entity.c source/engine/test_controller.c source/utils/config_loader.c source/main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS) 

.c.o:
	$(CC) -o $@ -c $(CFLAGS) $< 

clean:
	rm $(OBJECTS)
