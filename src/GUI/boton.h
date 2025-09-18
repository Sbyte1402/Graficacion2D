#pragma once

#include "../draw/figuras.h"

typedef struct _button{
    int x;
    int y;
    int width; 
    int height;
    Figuras label;
}Button;

void draw_boton(Button *button);
void eventListener(Button *button);

Figuras* createCuad(void);
Figuras* createCirc(void);
Figuras* createTrian(void);