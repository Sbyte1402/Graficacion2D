#include "boton.h"
#include "../render.h"
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

void eventListenerCreate(Button *button){    
    if(estadosrender.evento.motion.x >= button -> x &&
        estadosrender.evento.motion.x <= (button -> x + button -> width) &&
        estadosrender.evento.motion.y >= button -> y &&
        estadosrender.evento.motion.y <= (button -> y + button -> height) &&
        estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN){    
        
        if(button->label.cuadro.color.hex == 0xFFFFFFFF){
            switch(button -> label.data.type){
                case CUADRO:                
                    printf("Boton1 encontrado...\n");
                    Figuras *cuadrado = createCuad();

                    pushto_array(estadosrender.figuras_buffer, *cuadrado);
                    printf("Cuadrado creado...\n");
                    break;
                case CIRC:
                    printf("Boton2 encontrado...\n");
                    Figuras *circulo = createCirc();

                    pushto_array(estadosrender.figuras_buffer, *circulo);
                    printf("Circulo creado...\n");
                    break;
                case TRIAN:
                    printf("Boton3 encontrado...\n");
                    Figuras *triangulo = createTrian();

                    pushto_array(estadosrender.figuras_buffer, *triangulo);
                    printf("Triangulo creado...\n");
                    break;
                default:
                    break;    
            }
        }else{
            uint32_t color = button -> label.cuadro.color.hex;
            
            for(int i = 0; i < array_size(estadosrender.figuras_buffer); i++){
                estadosrender.figuras_buffer[i].
                cuadro.color.hex = color;
            }
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

Figuras* createCirc(){
    Figuras *circulo = (Figuras*)calloc(1, sizeof(Figuras));

    circulo -> circulo.pos.unpack.x = estadosrender.w_width / 2.f;
    circulo -> circulo.pos.unpack.y = estadosrender.w_height / 2.f;

    circulo -> circulo.r = 50;

    circulo -> circulo.color = (Color){0xFFFFFFFF};
    circulo -> circulo.type = CIRC;

    return circulo;
}

Figuras* createTrian(){
    Figuras *triangulo = (Figuras*)calloc(1, sizeof(Figuras));

    triangulo -> triangulo.pos[0] = (Vec2){{estadosrender.w_width / 8.f * 4,
                                            estadosrender.w_height / 2.f}};

    triangulo -> triangulo.pos[1] = (Vec2){{estadosrender.w_width / 2.f,
                                            estadosrender.w_height / 8.f * 3}};

    triangulo -> triangulo.pos[2] = (Vec2){{estadosrender.w_width / 8.f * 5,
                                            estadosrender.w_height / 2.f}};

    triangulo -> triangulo.color = (Color){0xFFFFFFFF};
    triangulo -> triangulo.type = TRIAN;

    return triangulo;
}