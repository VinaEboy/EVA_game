#include "Objects.h"
#include <stdlib.h>

Platform *create_platform(float x, float y, float width, float height) {
    Platform *new_platform = (Platform *) malloc(sizeof(Platform));
    if (!new_platform) return NULL;
    new_platform->x = x;
    new_platform->y = y;
    new_platform->width = width;
    new_platform->height = height;
    return new_platform;
}

void platform_destroy( Platform *platform) {
    free(platform);
}