CC=gcc
CFLAGS= -g -Wall
LDFLAGS= -lm -lSDL2
INCPATH= -I /home/thomas/code/sdl/C_SDL2/source/core/ \
		 -I /home/thomas/code/sdl/C_SDL2/source/utils/ \
		 -I /home/thomas/code/sdl/C_SDL2/source/modules/graphics/ \
		 -I /home/thomas/code/sdl/C_SDL2/source/modules/physics/ \
		 -I /home/thomas/code/sdl/C_SDL2/source/modules/collision/
SOURCES= \
		 source/core/entity.c \
		 source/core/test_controller.c \
		 source/core/sdl_wrapper.c \
		 source/utils/live_define.c \
		 source/utils/list.c \
		 source/utils/config_loader.c \
		 source/modules/graphics/fps_manager.c \
		 source/modules/graphics/sprite.c \
		 source/modules/graphics/graphics.c \
		 source/modules/physics/physics.c \
		 source/main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(INCPATH) $(OBJECTS) 

.c.o:
	$(CC) -o $@ $(INCPATH) -c $(CFLAGS) $< 

clean:
	rm $(OBJECTS)
