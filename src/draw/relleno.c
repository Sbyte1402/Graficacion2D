#include "draw.h"
#include "figuras.h"
#include "../global.h"
#include "../estructuras/pila.h"
#include "../memoria/memoria.h"

#include <stdlib.h>

void fill_flat_bottom(Vec2 p1,Vec2 p2, Vec2 p3, uint32_t color);
void fill_flat_top(Vec2 p1,Vec2 p2, Vec2 p3, uint32_t color);
void ordenar_y(Vec2 *y);

void fill_figura(void *figura, uint32_t fill_color){
    Figuras *figuraCast = (Figuras*)figura;
    switch(figuraCast -> data.type){
        case CIRC:{
            Circulo *circCast = (Circulo*)figuraCast;
            fill_flood(&(circCast -> pos), fill_color);
            break;}
        case CUADRO:{
            Cuadro *cuadCast = (Cuadro*)figuraCast;
            fill_flood(&(cuadCast -> pos), fill_color);
            break;}
        case TRIAN:{
            Triangulo *trianCast = (Triangulo*)figuraCast;
            fill_triangulo(trianCast, fill_color);
            break;}
        case LINEA:
            break;
        case CURVA:
            break;
    }
}

void fill_flood(Vec2 *pInicial, uint32_t fill_color){
    Pila *pila = NULL;
    char *verificado = (char*)calloc(estadosrender.w_height * estadosrender.w_width, sizeof(char));
    Vec2 *pixel = pInicial;
    int pos_pixel = (int)(pixel -> unpack.y) * estadosrender.w_width + (int)(pixel -> unpack.x);

    do{
        push(pila, pixel);

        if(pila){
            pixel = pop(pila);
            pos_pixel = (int)(pixel -> unpack.y) * estadosrender.w_width + (int)(pixel -> unpack.x);

            if(verificado[pos_pixel] == '0'){
                draw_pixel(pixel -> unpack.x, pixel -> unpack.y, fill_color);
                verificado[pos_pixel] = '1';
            }

            if(estadosrender.color_buffer[pos_pixel + 1] != fill_color && estadosrender.color_buffer[pos_pixel + 1] != estadosrender.clear_color.hex){
                if(verificado[pos_pixel + 1] == '0'){
                    Vec2 aux = {{pixel -> unpack.x + 1, pixel -> unpack.y}};
                    push(pila, &aux);
                }
            }

            if(estadosrender.color_buffer[pos_pixel - 1] != fill_color && estadosrender.color_buffer[pos_pixel - 1] != estadosrender.clear_color.hex){
                if(verificado[pos_pixel - 1] == '0'){
                    Vec2 aux = {{pixel -> unpack.x - 1, pixel -> unpack.y}};
                    push(pila, &aux);
                }
            }
            
            if(estadosrender.color_buffer[pos_pixel + estadosrender.w_width] != fill_color && estadosrender.color_buffer[pos_pixel + estadosrender.w_width] != estadosrender.clear_color.hex){
                if(verificado[pos_pixel + estadosrender.w_width] == '0'){
                    Vec2 aux = {{pixel -> unpack.x, pixel -> unpack.y + 1}};
                    push(pila, &aux);
                }
            }
            
            if(estadosrender.color_buffer[pos_pixel - estadosrender.w_width] != fill_color && estadosrender.color_buffer[pos_pixel - estadosrender.w_width] != estadosrender.clear_color.hex){
                if(verificado[pos_pixel - estadosrender.w_width] == '0'){
                    Vec2 aux = {{pixel -> unpack.x, pixel -> unpack.y - 1}};
                    push(pila, &aux);
                }
            }
        }
    }while(pila);

    free(verificado);
    freePila(pila);
}

void fill_triangulo(Triangulo *triangulo, uint32_t color){
    // Ordenar
    float cy, cx;

    Vec2 y[3] = {triangulo -> p1, triangulo -> p2, triangulo -> p3};
    ordenar_y(y);

    // Pintar
    if (y[1].unpack.y == y[2].unpack.y) {
        fill_flat_bottom(y[0], y[1], y[2], color);
    } else if (y[0].unpack.y == y[1].unpack.y) {
        fill_flat_top(y[0], y[1], y[2], color);
    } else {
        cy = y[1].unpack.y;
        cx = (y[1].unpack.y - y[0].unpack.y) * (y[2].unpack.x - y[0].unpack.x) / (y[2].unpack.y - y[0].unpack.y) + y[0].unpack.x;

        Vec2 v = {{cx, cy}};
        fill_flat_bottom(y[0], y[1], v, color);
        fill_flat_top(v, y[1], y[2], color);
    }
}

void ordenar_y(Vec2 *y){
    Vec2 aux;

    for(int i = 0; i < 3; i++){
        for(int j = i + 1; j < 3; j++){
            if(y[i].unpack.y > y[j].unpack.y){
                aux = y[i];
                y[i] = y[j];
                y[j] = aux;
            }
        }
    }
}

void fill_flat_bottom(Vec2 p2, Vec2 p3, Vec2 c, uint32_t color){
    float mi = (p3.unpack.x - p2.unpack.x) / (p3.unpack.y - p2.unpack.y);
    float mf = (c.unpack.x - p2.unpack.x) / (c.unpack.y - p2.unpack.y);

    float xi = p2.unpack.x;
    float xf = p2.unpack.x;

    for (int y = (int)p2.unpack.y; y <= (int)c.unpack.y; y++) {
        draw_linea(xi, y, xf, y, color);
        xi += mi;
        xf += mf;
    }
}

void fill_flat_top(Vec2 p1, Vec2 p2 ,Vec2 c, uint32_t color){
    float mi = (c.unpack.x - p1.unpack.x) / (c.unpack.y - p1.unpack.y);
    float mf = (c.unpack.x - p2.unpack.x) / (c.unpack.y - p2.unpack.y);

    float xi = c.unpack.x;
    float xf = c.unpack.x;

    for (int y = (int)c.unpack.y; y >= (int)p1.unpack.y; y--) {
        draw_linea(xi, y, xf, y, color);
        xi -= mi;
        xf -= mf;
    }
}