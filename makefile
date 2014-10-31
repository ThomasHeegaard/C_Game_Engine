CC=gcc
CFLAGS= -g -Wall
LDFLAGS= -lm -lSDL2
SOURCES= sdl_wrapper.c sprite.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS) 

.c.o:
	$(CC) -o $@ -c $(CFLAGS) $< 

clean:
	rm $(OBJECTS)
