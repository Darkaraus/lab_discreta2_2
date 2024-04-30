#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

u32 minGrado(u32* array_de_ids, u32 size_de_ese_array, Grafo G)
{
    u32 zaza = 0;
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
        return 1;
    } else if (minGrado(a->arr, a->size, G) > minGrado(b->arr, b->size, G))
    {
        return -1;
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