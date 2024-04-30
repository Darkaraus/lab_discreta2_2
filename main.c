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
    printf("Numero de vertices: %u\n", NumeroDeVertices(G));
    printf("Numero de lados. %u\n", NumeroDeLados(G));
    printf("Numero Delta: %u\n", Delta(G));
    
    u32 cantVertices = NumeroDeVertices(G);
    u32 Orden[cantVertices];
    // ------------- Orden Natural -------------
    for (u32 i = 0; i < cantVertices; i++)
    {
        Orden[i] = i;
    }
    printf("\n       ------------- Orden Natural -------------\nPrimer Greedy: %u\n",Greedy(G, Orden));
    color *coloreo_natural = malloc(cantVertices * sizeof(color));
    u32 chi_natural = Iterar(G, Orden, coloreo_natural, true);


    // ------------- Orden N-1 ... 0 -------------
    for (u32 i = 0; i < cantVertices; i++)
    {
        Orden[i] = (cantVertices - 1) - i;
    }
    printf("\n       ------------ Orden N-1 ... 0 ------------\nPrimer Greedy: %u\n",Greedy(G, Orden));
    color *coloreo_n1 = malloc(cantVertices * sizeof(color));
    u32 chi_n1 = Iterar(G, Orden, coloreo_n1, true);

    // ------------- Orden Par Decreciente, Impar creciente -------------
    u32 pares[cantVertices], size_pares;
    u32 impares[cantVertices], size_impares;
    size_impares = 0;
    size_pares = 0;
    for (u32 i = 0; i < cantVertices; i++)
    {
        if (i % 2 == 0)
        {
            pares[size_pares++] = i;
        } else {
            impares[size_impares++] = i;
        }
    }
    u32 index = 0;
    for (u32 i = 0; i < size_pares; i++)
    {
        Orden[index++] = pares[(size_pares - 1) - i];
    }
    for (u32 i = 0; i < size_impares; i++)
    {
        Orden[index++] = impares[i];
    }
    printf("\n       ------------ Orden par impar ------------\nPrimer Greedy: %u\n", Greedy(G, Orden));
    color *coloreo_parimpar = malloc(cantVertices * sizeof(color));
    u32 chi_parimpar = Iterar(G, Orden, coloreo_parimpar, true);


    // ------------- Orden Grados -------------
    for (u32 i = 0; i < cantVertices; i++)
    {
        Orden[i] = i;
    }
    qsort_r(Orden, cantVertices, sizeof(u32), compGrados, G);
    printf("\n       -------------- Orden Grados -------------\nPrimer Greedy: %u\n",Greedy(G, Orden));
    color *coloreo_grado = malloc(cantVertices * sizeof(color));
    u32 chi_grado = Iterar(G, Orden, coloreo_grado, true);
    
    // ----------------- Me canse de ordenar cosas -----------------------
    if (chi_grado <= chi_parimpar && chi_grado <= chi_n1 && chi_grado <= chi_natural) {
        Iterar(G, Orden, coloreo_grado, false);
    } 
    else if (chi_parimpar <= chi_grado && chi_parimpar <= chi_n1 && chi_parimpar <= chi_natural) {
        Iterar(G, Orden, coloreo_parimpar, false);
    } 
    else if (chi_n1 <= chi_grado && chi_n1 <= chi_parimpar && chi_n1 <= chi_natural) {
        Iterar(G, Orden, coloreo_n1, false);
    } 
    else {
        Iterar(G, Orden, coloreo_natural, false);
    }


    free(coloreo_grado);free(coloreo_n1);free(coloreo_natural);free(coloreo_parimpar);
    DestruirGrafo(G);
    return 0;
}

/*
___________________          _-_
\==============_=_/ ____.---'---`---.____
            \_ \    \----._________.----/
              \ \   /  /    `-_-'
          __,--`.`-'..'-_
         /____          ||
              `--.____,-'
*/