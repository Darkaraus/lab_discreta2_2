#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "API2024Parte2.h"

bool checkOrden(u32 size, u32* Orden)
{

    // array de bools...
    bool *found_vertices = malloc(size * sizeof(bool));

    // Error por si no funca malloc...
    if (found_vertices == NULL)
    {
        return false;
    }

    // Lo lleno de false (no encontro ninguna aun xd)
    for (size_t i = 0; i < size; i++)
    {
        found_vertices[i] = false;
    }

    bool founded = true;
    for (size_t i = 0; i < size; i++)
    {
        // Obvio no hay vertices > size, van de 0 a n
        if (Orden[i] < size)
        {
            // Si ya la encontro entonces no hay biyeccion  
            if (found_vertices[Orden[i]])
            {
                founded = false;
            }
        
            found_vertices[Orden[i]] = true; 
            
        } else {
            founded = false;
        }
    }
    free(found_vertices);
    return founded;
}

int CompareColor(const void *a, const void *b, void *arg) {
    struct argumentos *args = (struct argumentos*)arg;
    u32 vertexA = *(u32*)a;
    u32 vertexB = *(u32*)b;
    u32 colorA = Color(vertexA, args->grafo);
    u32 colorB = Color(vertexB, args->grafo);
    
    if (args->arr[colorA] < args->arr[colorB]) {
        return -1; // Orden descendente
    } else if (args->arr[colorA] > args->arr[colorB]) {
        return 1; // Orden descendente
    } else if (colorA > colorB){
        return 1; // Los elementos son iguales
    } else if (colorA < colorB){
        return -1; // Los elementos son iguales
    } else {
        return 0; // Los elementos son iguales
    }
}

u32 minGrado(u32* array_de_ids, u32 size_de_ese_array, Grafo G)
{
    u32 zaza = POTENCIA;
    for (u32 i = 0; i < size_de_ese_array; i++)
    {
        if (zaza > Grado(array_de_ids[i], G))
        {
            zaza = Grado(array_de_ids[i], G);
        } 
    }
    
    return zaza;
}

u32 maxGrado(u32* array_de_ids, u32 size_de_ese_array, Grafo G)
{
    u32 zaza = 0;
    for (u32 i = 0; i < size_de_ese_array; i++)
    {
        if (zaza < Grado(array_de_ids[i], G))
        {
            zaza = Grado(array_de_ids[i], G);
        } 
    }
    
    return zaza;
}

u32 m(struct ArrayConTamaño *a, struct ArrayConTamaño *b, Grafo G)
{
    if (minGrado(a->arr, a->size, G) < minGrado(b->arr, b->size, G))
    {
        return -1;
    } else if (minGrado(a->arr, a->size, G) > minGrado(b->arr, b->size, G))
    {
        return 1;
    } else {
        return 0;
    }
}

u32 M(struct ArrayConTamaño *a, struct ArrayConTamaño *b, Grafo G)
{
    if (maxGrado(a->arr, a->size, G) < maxGrado(b->arr, b->size, G))
    {
        return 1;
    } else if (maxGrado(a->arr, a->size, G) > maxGrado(b->arr, b->size, G))
    {
        return -1;
    } else {
        return 0;
    }
}

u32 M_m(struct ArrayConTamaño *a, struct ArrayConTamaño *b, Grafo G)
{
    u32 valor_a = maxGrado(a->arr, a->size, G) + minGrado(a->arr, a->size, G);
    u32 valor_b = maxGrado(b->arr, b->size, G) + minGrado(b->arr, b->size, G);
    if (valor_a < valor_b)
    {
        return 1;
    } else if (valor_a > valor_b)
    {
        return -1;
    } else {
        return 0;
    }
}

u32 compGrados(u32 a, u32 b, Grafo G)
{
    if (Grado(a, G) < Grado(a, G))
    {
        return 1;
    } else if (Grado(a, G) > Grado(b, G))
    {
        return -1;
    } else {
        return 0;
    }
}

u32 Iterar(Grafo G, u32 *Orden, u32 *coloreo, bool mode)
{
    if (mode)
    {
        for (u32 i = 0; i < 50; i++)
        {
            GulDukat(G, Orden);
            printf(" %u ",Greedy(G, Orden));
            ElimGarak(G, Orden);
            printf(" %u ",Greedy(G, Orden));
            if ((i + 1) % 10 == 0)
            {
                printf("\n");
            }
        }
        u32 resultado = Greedy(G, Orden);
        ExtraerColores(G, coloreo);
        return resultado;
         
    } else {
        ImportarColores(coloreo, G);
        srand(time(NULL)); // le pone a rand el tiempo del usuario, asi sera realmente random ):D
        int random = rand() % 2;
        if (random == 1)
        {
            printf("\n\nOrden Seleccionado: GulDukat\n");
            for (u32 i = 0; i < 500; i++)
            {
                GulDukat(G, Orden);
                Greedy(G, Orden);
            }
            printf("Iterando 500 veces...\nChi Aproximado: %u \n",Greedy(G, Orden));
            return POTENCIA;
        } else {
            printf("\n\nOrden Seleccionado: ElimGarak\n");
            for (u32 i = 0; i < 500; i++)
            {
                ElimGarak(G, Orden);
                Greedy(G, Orden);
            }
            printf("Iterando 500 veces...\nChi Aproximado: %u \n",Greedy(G, Orden));
            return POTENCIA;
        }        
    }
}
