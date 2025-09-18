#include "boton.h"
#include "../global.h"
#include "../draw/draw.h"
#include "../draw/figuras.h"
#include "../memoria/memoria.h"

#include <stdlib.h>
#include <stdio.h>

void draw_boton(Button *button){
    draw_cuadrado(button -> x, button -> y,
                  button -> width, button -> height,
                  0xFFFFFFFF);

    draw_figura(&(button -> label));
}

void eventListener(Button *button){    
    if(estadosrender.evento.motion.x >= button -> x &&
        estadosrender.evento.motion.x <= (button -> x + button -> width) &&
        estadosrender.evento.motion.y >= button -> y &&
        estadosrender.evento.motion.y <= (button -> y + button -> height) &&
        estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN){    
        
        switch(button -> label.data.type){
            case CUADRO:                
                printf("Boton1 encontrado...\n");
                Figuras *prueba = createCuad();

                pushto_array(estadosrender.figuras_buffer, *prueba);
                break;
            case CIRC:
                printf("Boton2 encontrado...\n");
                break;
            case TRIAN:
                printf("Boton3 encontrado...\n");
                break;
            case LINEA:
                break;
            case CURVA:
                break;    
        }
    }
}

Figuras* createCuad(){
    Figuras *cuadro = (Figuras*)calloc(1, sizeof(Figuras));

    cuadro -> cuadro.pos.unpack.x = estadosrender.w_width / 3.f;
    cuadro -> cuadro.pos.unpack.y = estadosrender.w_height / 3.f;

    cuadro -> cuadro.w = 100;
    cuadro -> cuadro.h = 100;

    cuadro -> cuadro.color = (Color){0xFFFFFFFF};
    cuadro -> cuadro.type = CUADRO;

    return cuadro;
}