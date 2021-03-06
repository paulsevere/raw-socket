CC=gcc
CCFLAGS=-Wall
LDFLAGS=
SOURCES=$(wildcard **/*.c) server.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=./server
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%/%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $<

%/%.o: %/%.c
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f **/*.o *.o $(TARGET)
