#ifndef __OBJECTS__
#define __OBJECTS__

typedef struct {
    float x, y;     // Posição do canto superior esquerdo da plataforma
    float width;    // Largura da plataforma
    float height;   // Altura da plataforma (geralmente não muito importante para o chão)
} Platform;

Platform *create_platform(float x, float y, float width, float height);

void platform_destroy( Platform *platform);

#endif