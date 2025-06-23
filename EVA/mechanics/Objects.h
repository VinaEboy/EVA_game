#ifndef __OBJECTS__
#define __OBJECTS__

// um arquivo com os objetos de fase
// só tem as plataformas porque não foram feitos objetos de fase
// mas se tivessem mais (como caixas, portas...) estariam aqui

typedef struct {
    float x, y;     // Posição do canto superior esquerdo da plataforma
    float width;    // Largura da plataforma
    float height;   // Altura da plataforma 
} Platform;

//cria a plataforma
Platform *create_platform(float x, float y, float width, float height);

//libera memória
void platform_destroy( Platform *platform);

#endif