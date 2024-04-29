#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "API2024Parte2.h"

#define POTENCIA 4294967295U

// No hace falta chequear el tamaño de Orden, siempre es n, consigna. 
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

u32 m(u32 a, u32 b, Grafo G)
{
    if (Grado(a, G) > Grado(b, G))
    {
        return -1;
    } else if (Grado(a, G) < Grado(b, G))
    {
        return 1;
    } else {
        return 0;
    }
}

u32 M(struct ArrayConTamaño *a, struct ArrayConTamaño *b, Grafo G)
{
    printf(" %u ", a->arr[0]);
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



u32 Greedy(Grafo G,u32* Orden)
{
    // Chequeo del orden ------------------------
    u32 cantVertice = NumeroDeVertices(G); 
    bool is_biyeccion = checkOrden(cantVertice, Orden);
    if (!is_biyeccion) // 
    {
        printf("Orden No Biyectivo\n");
        return(POTENCIA);
    }
    printf("Orden Biyectivo\n");

    // Vuelvo colores a 0
    for (size_t i = 0; i < cantVertice; i++)
    {
        AsignarColor(0, i, G);
    }

    // Greedy -----------------------------------
    u32 corMax = 0;
    for (size_t i = 0; i < cantVertice; i++)
    {
        bool coloresUsados[cantVertice + 1]; // Array de colores usados
        memset(coloresUsados, false, sizeof(coloresUsados)); // Inicializamos en false

        for (size_t k = 0; k < Grado(Orden[i], G); k++) 
        {                                               
            u32 vecinoID = Vecino(k, Orden[i], G); // id del vecino
            u32 colorVecino = Color(vecinoID, G);
            coloresUsados[colorVecino] = true; // Marcamos el color del vecino como usado
        } 

        // Buscamos el primer color que no esté en uso
        u32 cor = 1;
        while (coloresUsados[cor]) 
        {
            cor++;
        }
        
        AsignarColor(cor, Orden[i], G);

        if (cor > corMax)
        {
            corMax = cor;
        }
    }
    
    
    printf("Maximo color: %u\n", corMax);
    printf("Numeros lados: %u\n", NumeroDeLados(G));
    printf("----------  G R E E D Y    C O M P L E T O ----------\n");
    return corMax;
}

char GulDukat(Grafo G,u32* Orden) // <!!!> Leer todos los comentarios, Hacete un mate o un cafe <!!!>
{   
    u32 cantVertice = NumeroDeVertices(G);
    color *vertColores = malloc(NumeroDeVertices(G) * sizeof(color));
    if (vertColores == NULL)
    {
        return '1'; // si da error devuelve esto, consigna
    }
   
    ExtraerColores(G, vertColores);
    u32 corMax = 1;
    // Consigo la cantidad de colores de manera horrible, NO PENSARLA MUCHO
    for (size_t i = 0; i < cantVertice; i++)
    {
        if (corMax < vertColores[i])
        {
            corMax = vertColores[i];
        }
    }
    free(vertColores); // El array solo fue usado para conseguir el color maximo... Era para darle uso a ExtraerColores, para que sirve si no? capaz sirva jajaja
    // REINICIAR CEREBRO, solo conseguimos el color maximo

    struct ArrayConTamaño Div4[cantVertice];
    struct ArrayConTamaño Par[cantVertice];
    struct ArrayConTamaño Impar[cantVertice];

    // Inicializamos tamaños
    for (u32 i = 0; i < cantVertice; i++)
    {
        Div4[i].size = 0;
        Par[i].size = 0;
        Impar[i].size = 0;
    }


    u32 index_Div4 = 0; // de paso en estos index queda el tamaño del array grande 
    u32 index_Par = 0;
    u32 index_Impar = 0;

    for (u32 cor = 0; cor <= corMax; cor++)
    {
        u32 *divisibles4 = malloc(cantVertice * sizeof(u32)); // array temporales para cada color. Se ordenan y se añaden al grande de su categoria (PROGAMACION!!!)
        u32 *pares = malloc(cantVertice * sizeof(u32));
        u32 *impares = malloc(cantVertice * sizeof(u32));

        u32 size_divisibles4 = 0;
        u32 size_pares = 0;
        u32 size_impares = 0;

        for (u32 i = 0; i < cantVertice; i++)
        {
            if (Color(i, G) == cor)
            {
                if (cor % 4 == 0)
                {
                    divisibles4[size_divisibles4++] = i;
                    //printf("  Vertice con color divisible por 4: %u\n", i);
                }
                else if (cor % 2 == 0 && cor % 4 != 0)
                {
                    pares[size_pares++] = i;
    
                    //printf("  Vertice con color divisible solo por 2: %u\n", i);
                }
                else
                {
                    impares[size_impares++] = i;
                    //printf("  Vertice con color divisible impar: %u\n", i);
                }
            }
        }

        // SIEMPRE AÑADIIIIR <-------- nuevo 4/29/2024
        if (size_divisibles4 != 0) 
        {
            Div4[index_Div4].size = size_divisibles4;
            Div4[index_Div4++].arr = divisibles4;
            
        } else if (size_pares != 0)
        {
            Par[index_Par].size = size_pares;
            Par[index_Par++].arr = pares;
            
        } else if (size_impares != 0)
        {
            Impar[index_Impar].size = size_impares;
            Impar[index_Impar++].arr = impares;
            
        } // No biyectivo por que no lo metemos en Orden
    }
    
    u32 index = 0;
    printf("\n\n");
    qsort_r(Div4, index_Div4, sizeof(struct ArrayConTamaño), M, G);
    printf("        Cantidad de colores div4: %u\n", index_Div4);
    for (u32 i = 0; i < index_Div4; i++)
    {   
        printf("        Cantidad de color %u: %u\n", Color(Div4[i].arr[0],G), Div4[i].size);
        printf("        Vertices con color %u:       ", Color(Div4[i].arr[0],G));
        for (u32 j = 0; j < Div4[i].size; j++)
        {
            printf(" %u ", Div4[i].arr[j]);
            Orden[index++] = Div4[i].arr[j];
        }
        free(Div4[i].arr);
    }
    printf("\n\n");
    qsort_r(Par, index_Par, sizeof(struct ArrayConTamaño), M, G);
    printf("        Cantidad de colores pares: %u\n", index_Par);
    for (u32 i = 0; i < index_Par; i++)
    {
        printf("        Cantidad de color %u: %u\n", Color(Par[i].arr[0], G), Par[i].size);
        printf("        Vertices con color %u:       ", Color(Par[i].arr[0], G));
        for (u32 j = 0; j < Par[i].size; j++)
        {
            printf(" %u ", Par[i].arr[j]);
            Orden[index++] = Par[i].arr[j];
        }
        printf("\n");
        free(Par[i].arr);
    }
    printf("\n\n");
    qsort_r(Impar, index_Impar, sizeof(struct ArrayConTamaño), M, G);
    printf("        Cantidad de colores impares: %u\n", index_Impar);
    for (u32 i = 0; i < index_Impar; i++)
    {
        printf("        Cantidad de color %u: %u\n", Color(Impar[i].arr[0], G), Impar[i].size);
        printf("        Vertices con color %u:       ", Color(Impar[i].arr[0], G));
        printf("[");
        for (u32 j = 0; j < Impar[i].size; j++)
        {
            printf(" %u ", Impar[i].arr[j]);
            Orden[index++] = Impar[i].arr[j];
        }
        printf("]\n");
        free(Impar[i].arr);
    }
    printf("\n\n");
    printf("Nuevo orden mundial: \n");
    printf("id:   ");
    for (u32 i = 0; i < cantVertice; i++)
    {
        printf(" %u ", Orden[i]);
    }
    printf("\ncolor:");
    for (u32 i = 0; i < cantVertice; i++)
    {
        printf(" %u ", Color(Orden[i], G));
    }
    printf("\ngrado:");
    for (u32 i = 0; i < cantVertice; i++)
    {
        printf(" %u ", Grado(Orden[i], G));
    }
    printf("\n\n");
   
    printf("index_Div4: %u, index_Par: %u, index_Impar: %u\n", index_Div4, index_Par, index_Impar);

    return '0'; // si esta bien devuelve esto, consigna
}