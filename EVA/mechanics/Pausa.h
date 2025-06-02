#ifndef __PAUSA__
#define __PAUSA__

typedef struct {
    unsigned char apertou_pausa;
    unsigned char pausa;
    unsigned char apertou_inventario;
    unsigned char inventario;
} menu;

void menu_create();
void open_pause();
void open_inventory();

void close_pause();
void close_inventory();
void menu_destroy();
