// Archivo main para probar las funciones de la biblioteca APIG24.h

#include "API2024Parte2.h"
#include <stdio.h>
#include <stdlib.h>
#include "EstructuraGrafo24.h"

int main()
{
    Grafo G = ConstruirGrafo();
    if (G == NULL)
    {
        printf("Error al construir el grafo\n");
        return 1;
    }

    // Si o si el tamaño de Orden tiene que ser la cantidad de vertices, por la consigna.
    
    u32 Orden[1072];
    GulDukat(G, Orden); // Al principio, todos colores 0, es el orden natural, 0,1,2,3,...
    Greedy(G, Orden);

    u32 Dios[1072];
    GulDukat(G, Dios);
    Greedy(G, Dios);
    
    /* 
    printf("Numero de vertices: %d\n", NumeroDeVertices(G));
    printf("Numero de lados: %d\n", NumeroDeLados(G));
    printf("Delta: %d\n", Delta(G));
    
    for (u32 i = 0; i < NumeroDeVertices(G); i++)
    {
        u32 grado = G->vertices[i].grado;
        color color = G->vertices[i].color;
        printf("Grado del vertice %d: %d\n", i, grado);
        printf("Color del vertice %d: %d\n", i, color);
        printf("Vecinos del vertice %d: ", i);
        for (u32 j = 0; j < G->vertices[i].grado; j++){
            printf("%d ",G->vertices[i].vecinos[j]);   
        }
        printf("\n");
    } 
    
    */

/*     printf("Color del vertice 0: %u \n", Color(0, G));
    printf("Vecino 0 del vertice 0: %d\n", Vecino(0, 0, G));
    // Numero de vertices
    printf("Numero de vertices: %d\n", NumeroDeVertices(G));
    // Numero de lados
    printf("Numero de lados: %d\n", NumeroDeLados(G));
    // Delta
    printf("Delta: %d\n", Delta(G));
    // Grado
    printf("Grado del vertice 0: %d\n", Grado(0, G)); */

    DestruirGrafo(G);
    return 0;
}