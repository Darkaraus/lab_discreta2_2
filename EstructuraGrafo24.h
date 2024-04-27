#ifndef EstructuraGrafo24_H
#define EstructuraGrafo24_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int u32; 
typedef u32 color;

struct Vertice{
    color color;
    u32 grado;
    u32 *vecinos;
};

struct GrafoSt{
    u32 delta; //delta
    u32 cant_vertices; //Cantidad de vertices 
    u32 cant_lados; //Cantidad de lados
    struct Vertice *vertices; // Array de vertices
};
#endif 