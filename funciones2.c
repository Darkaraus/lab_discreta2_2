#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // para memset
#include "API2024Parte2.h"



// No hace falta chequear el tamaño de Orden, siempre es n, consigna. 

u32 Greedy(Grafo G,u32* Orden)
{
    // Chequeo del orden ------------------------
    u32 cantVertice = NumeroDeVertices(G); 
    bool is_biyeccion = checkOrden(cantVertice, Orden);
    if (!is_biyeccion) // 
    {
        return(POTENCIA);
    }

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
        if (divisibles4 == NULL || pares == NULL || impares == NULL)
        {
            return '1';
        }
        

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
                }
                else if (cor % 2 == 0 && cor % 4 != 0)
                {
                    pares[size_pares++] = i;
                }
                else
                {
                    impares[size_impares++] = i;
                }
            }
        }

        if (size_divisibles4 != 0) 
        {
            Div4[index_Div4].size = size_divisibles4;
            Div4[index_Div4++].arr = divisibles4;
        } 
        else 
        {
            free(divisibles4);
        }

        if (size_pares != 0)
        {
            Par[index_Par].size = size_pares;
            Par[index_Par++].arr = pares;
        } 
        else 
        {
            free(pares);
        }

        if (size_impares != 0)
        {
            Impar[index_Impar].size = size_impares;
            Impar[index_Impar++].arr = impares;
        } 
        else 
        {
            free(impares);
        }
    }
    
    u32 index = 0;

    qsort_r(Div4, index_Div4, sizeof(struct ArrayConTamaño), M, G);
    for (u32 i = 0; i < index_Div4; i++)
    {   
        for (u32 j = 0; j < Div4[i].size; j++)
        {
            Orden[index++] = Div4[i].arr[j];
        }
        free(Div4[i].arr);
    }
    
    qsort_r(Par, index_Par, sizeof(struct ArrayConTamaño), M_m, G);
    for (u32 i = 0; i < index_Par; i++)
    {
        for (u32 j = 0; j < Par[i].size; j++)
        {
            Orden[index++] = Par[i].arr[j];
        }
        free(Par[i].arr);
    }

    qsort_r(Impar, index_Impar, sizeof(struct ArrayConTamaño), m, G);
    for (u32 i = 0; i < index_Impar; i++)
    {
        for (u32 j = 0; j < Impar[i].size; j++)
        {
            Orden[index++] = Impar[i].arr[j];
        }
        free(Impar[i].arr);
    }

    return '0'; // si esta bien devuelve esto, consigna
}

char ElimGarak(Grafo G,u32* Orden)
{   
    color *vertColores = calloc(NumeroDeVertices(G), sizeof(color));
    ExtraerColores(G, vertColores);
    u32 *CantVecesColor = calloc(NumeroDeVertices(G), sizeof(u32));
    u32 Vertices[NumeroDeVertices(G)];
    bool f1 = true; //Solo necesitamos que la cardinalidaad de 1 y 2 se asignen una vez
    bool f2 = true;

    //Creamos el arreglo con los vertices ordenados por cardinalidad
    /*  Cuando encontremos un vertice con color 1 le asignamos la cardinalidad maxima, cuando encontremos uno con 2
        Con el resto simplemente en relacion a cuantas veces ocurren    */
    //Tomo el array de colores, para determinar la cantidad de veces que se uso cada color 
    for (u32 i = 0; i < NumeroDeVertices(G); i++)
    {   
        Vertices[i] = i;
        if (vertColores[i] == 2 && f2){
            CantVecesColor[vertColores[i]] = NumeroDeVertices(G) - 1;
            f2 = false;
        } else if (vertColores[i] == 1 && f1){
            CantVecesColor[vertColores[i]] = NumeroDeVertices(G);
            f1 = false;
        } else if (vertColores[i] != 1 && vertColores[i] != 2){
            CantVecesColor[vertColores[i]]++;
        }
    }
    //Entonces en CantVecesColor[1] tengo la cantidad de veces que se uso el color 1

    
    struct argumentos args;
    args.arr = CantVecesColor;
    args.grafo = G;

    //mergeSort(Vertices, 0, NumeroDeVertices(G) - 1, CantVecesColor, G);
    qsort_r(Vertices, NumeroDeVertices(G), sizeof(u32), CompareColor, &args);

    for (u32 i = 0; i < NumeroDeVertices(G); i++)
    {
        Orden[i] = Vertices[i];
    }

    free(vertColores);
    free(CantVecesColor);
    return 0;
}