CC=gcc
CFLAGS= -g -Wall
LDFLAGS= -lm -lSDL2
INCPATH= -I engine/collision/ \
		 -I engine/debug/ \
		 -I engine/entity/ \
		 -I engine/graphics/ \
		 -I engine/physics/ \
		 -I engine/sdl_wrapper/ \
		 -I engine/utils/ \
		 -I game/ \

SOURCES= \
		engine/collision/collision.c \
		engine/collision/collision_object.c \
		engine/debug/debug.c \
		engine/entity/entity.c \
		engine/graphics/draw.c \
		engine/graphics/fps_manager.c \
		engine/graphics/graphics.c \
		engine/graphics/sprite.c \
		engine/physics/physics.c \
		engine/sdl_wrapper/sdl_wrapper.c \
		engine/utils/config_loader.c \
		engine/utils/extra_math.c \
		engine/utils/list.c \
		game/live_define.c \
		game/test_controller.c \
		game/main.c
		

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(INCPATH) $(OBJECTS) 

.c.o:
	$(CC) -o $@ $(INCPATH) -c $(CFLAGS) $< 

clean:
	rm $(OBJECTS)
