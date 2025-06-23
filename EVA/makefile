TARGET = EVA

CC = gcc

#o shell é o caminho para as bibliotecas dos Allegro no computador que está rodando
CFLAGS = -Wall -g $(shell pkg-config --cflags allegro-5 allegro_main-5 allegro_font-5 \
  allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)


LDLIBS = -lm $(shell pkg-config --libs allegro-5 allegro_main-5 allegro_font-5 \
  allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)


MAIN_SOURCES = main.c
SRC_DIRS = entities gameflow items mechanics levels #as pastas com compiláveis
SUB_SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
SOURCES = $(MAIN_SOURCES) $(SUB_SOURCES)
OBJECTS = $(SOURCES:.c=.o)


all: $(TARGET)


$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
