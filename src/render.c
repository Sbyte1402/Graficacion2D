#include "render.h"
#include "draw/draw.h"
#include "draw/linea.h"
#include "math/lerp.h"
#include "math/vectores.h"
#include "draw/figuras.h"
#include "memoria/memoria.h"
#include "color/colores.h"

#include <math.h>
#include <stdio.h>

Vec2 *punto_seleccionado = NULL;

Vec2* pivote_mas_cerca(Vec2 mp, Figuras *figs, float umbral){
    
    int a = 0;
    int b = array_size(figs) - 1;
    
    float low;
    float high;
    float centro;
    for(int i = 0; i < array_size(figs); i++){
        int r = (a + b) / 2;
        low = distanciav2(mp, figs[a].cuadro.pos);
        high = distanciav2(mp, figs[b].cuadro.pos);
        centro = distanciav2(mp, figs[r].cuadro.pos);

        if(fabs(low) <= umbral){
            return &figs[a].cuadro.pos;
        } else if (fabs(high) <= umbral) {
            return &figs[b].cuadro.pos;
        } else if (fabs(centro) <= umbral){
            return &figs[r].cuadro.pos;
        }

        if(r < b){
            b = r;
        } else if (r > a){
            a = r;
        }
    }

    return NULL;
}

void render_input(void){
    if(estadosrender.evento.type == SDL_EVENT_QUIT){
        estadosrender.run = 0;
    }

    if(estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        // Buscar el pivote mas cerca
        // Obtener referencia de la figura
        // Modificar
        printf("(%.3f, %.3f)\n", estadosrender.evento.motion.x, estadosrender.evento.motion.y);

        Vec2 *pivote = pivote_mas_cerca((Vec2){{estadosrender.evento.motion.x,
                                               estadosrender.evento.motion.y}},
                                               estadosrender.figuras_buffer,
                                               10.f);

        if(!punto_seleccionado){
            punto_seleccionado = pivote_mas_cerca((Vec2){{estadosrender.evento.motion.x,
                                                          estadosrender.evento.motion.y}},
                                                          estadosrender.figuras_buffer,
                                                          10.f);
        }

        if(punto_seleccionado){
            printf("Punto cercano (%.3f, %.3f)\n",pivote -> unpack.x, pivote -> unpack.y);
        }
    } else if (estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_UP){
        // Modificar la figura
        if(punto_seleccionado){
            punto_seleccionado->unpack.x = estadosrender.evento.motion.x;
            punto_seleccionado->unpack.y = estadosrender.evento.motion.y;
            punto_seleccionado = NULL;
        }
    }
}

void clear_color_buffer(){
    for(int y = 0; y < estadosrender.w_height; ++y){
        for(int x = 0; x < estadosrender.w_width; ++x){
            draw_pixel(x, y, estadosrender.clear_color.hex);
        }
    }
}

void copy_buffer_to_texture(){
    SDL_UpdateTexture(estadosrender.texture, 
                      NULL, 
                      estadosrender.color_buffer, 
                      (int)(estadosrender.w_width * sizeof(int)));

    SDL_RenderTexture(estadosrender.renderer, 
                      estadosrender.texture, 
                      NULL, 
                      NULL);
}

void _Init(){
    Vec2 pc1 = {{400.f, 360.f}};
    Vec2 pc2 = {{600.f, 100.f}};
    Vec2 pc3 = {{800.f, 360.f}};
    
    Linea linea = {
        .p1 = (Vec2){{800, 100}},
        .p2 = (Vec2){{600, 250}},
        .offset_mem1 = {0},
        .color = (Color){0xAB00ABFF},
        .type = LINEA
    };

    Curva curva = {
        .p1 = pc1,
        .p2 = pc2,
        .p3 = pc3,
        .color = (Color){0xFFFF00FF},
        .type = CURVA
    };

    Circulo circ = {
        .pos = {{estadosrender.w_width/2.f, estadosrender.w_height/2.f}},
        .r = 20.f,
        .vert = 32,
        .offset_mem1 = {0},
        .color = (Color){0x00FFFFFF},
        .type = CIRC
    };

    Cuadro cuadro = {
        .pos = {.unpack = {.x = 140, .y = 140}},
        .h = 200,
        .w = 200,
        .offset_mem1 = {0},
        .color = (Color){0x140140FF},
        .type = CUADRO
    };

    Triangulo triangulo = {
        .p1 = {.unpack = {.x = 400, .y = 360}},
        .p2 = {.unpack = {.x = 600, .y = 100}},
        .p3 = {.unpack = {.x = 800, .y = 360}},
        .color = (Color){0x2AADBFFF},
        .type = TRIAN
    };

    Figuras test = {.linea = linea};
    Figuras test2 = {.curva = curva};
    Figuras test3 = {.circulo = circ};
    Figuras test4 = {.cuadro = cuadro};
    Figuras test5 = {.triangulo = triangulo};

    pushto_array(estadosrender.figuras_buffer, test);
    pushto_array(estadosrender.figuras_buffer, test2);
    pushto_array(estadosrender.figuras_buffer, test3);
    pushto_array(estadosrender.figuras_buffer, test4);
    pushto_array(estadosrender.figuras_buffer, test5);
}

void update(){
    // Color VERDE = {0x00FF00FF};
    // Color AZUL = {0x0000FFFF};
    {
    // Linea gruesa degradado de color
    // float t;
    // for(int i = -10; i < 10; i++){
    //     int y = estadosrender.w_height / 2.f + i;
    //     for(int x = 0; x < estadosrender.w_width; ++x){
    //         t = x / (float)estadosrender.w_width;
    //         draw_pixel(x, y, lerp_color(AZUL, VERDE, t).hex);
    //     }
    // }
    }
    {
    // traingulo dado 3 puntos
    // int x0 = 25;
    // int y0 = 32;
    // int x1 = 400;
    // int y1 = 80;
    // int x2 = 800;
    // int y2 = 400;

    // draw_trian(x0, y0, x1, y1, x2, y2, AZUL.hex);
    }
    {
        // cuadrado dado un punto
        // int x0 = 140;
        // int y0 = 540;
        // int ancho = 222;
        // int alto = 76;
        // draw_cuadrado(x0, y0, ancho, alto, AZUL.hex);
    }
    {
        // draw_circuloTrig(100, 400, 400, 32, AZUL.hex);
        // draw_circuloPM(200, 400, 400, AZUL.hex);
    }
    {
        // draw_cuadrado(400, 200, 250, 200, AZUL.hex);    // Enfrente
        // draw_trian(400, 200, 650, 200, 525, 110, AZUL.hex); // Techo frente
        // draw_linea(650, 400, 800, 330, AZUL.hex);   // Costado bajo
        // draw_linea(650, 200, 800, 130, AZUL.hex);   // Costado alto
        // draw_linea(800,330, 800, 130, AZUL.hex);    // Costado derecha
        // draw_linea(525, 110, 650, 70, AZUL.hex);    // Techo arriba
        // draw_linea(650, 70, 800, 130, AZUL.hex);    // Techo derecha
        // draw_circuloPM(100, 100, 100, AZUL.hex);    // Sol
        // draw_cuadrado(480, 310, 60, 90, AZUL.hex);  // Puerta
        // draw_cuadrado(420, 220, 50, 50, AZUL.hex);  // Ventana izq
        // draw_cuadrado(580, 220, 50, 50, AZUL.hex);  // Ventana der
        // draw_linea(0, 310, 400, 310, AZUL.hex); // Piso izq
        // draw_linea(800, 310, 1080, 310, AZUL.hex);  // Piso der
        // draw_circuloPM(200, 0, 720, AZUL.hex);
        // draw_circuloPM(200, 1080, 720, AZUL.hex);
    }   
    {
        // Vec2 v1 = {.unpack = {.x = 100, .y = 300}};
        // Vec2 v2 = {.unpack = {.x = 600, .y = 300}};
        // Vec2 v3 = {.unpack = {.x = 200, .y = 30}};

        // Vec2 ctrlV;

        // for(float t = 0; t <= 1; t += 0.001){
        //     ctrlV = lerp2v2(v1, v3, v2, t);
        //     draw_pixel(ctrlV.unpack.x, ctrlV.unpack.y, AZUL.hex);
        // }
    }
    {
    // draw_figura(&test);
    // draw_figura(&test2);
    // draw_figura(&test3);
    // draw_figura(&test4);
    // draw_figura(&test5);
    }

    // Ciclo del draw
    for(int i = 0; i < array_size(estadosrender.figuras_buffer); i++){
        draw_figura(&estadosrender.figuras_buffer[i]);
    }
}

void render_frame(){
    SDL_RenderPresent(estadosrender.renderer);
}