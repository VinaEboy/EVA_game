TARGET = EVA
CC = gcc
CFLAGS = -Wall -g -lm -fsanitize=address $(shell pkg-config --cflags allegro-5 allegro_main-5 allegro_font-5 \
  allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)

LDLIBS =  $(shell pkg-config --libs allegro-5 allegro_main-5 allegro_font-5 \
  allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
LDFLAGS = -fsanitize=address

MAIN_SOURCES = main.c 

SRC_DIRS = entities gameflow items mechanics
SUB_SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

SOURCES = $(MAIN_SOURCES) $(SUB_SOURCES)

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDLIBS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(ALLEGRO_FLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)
