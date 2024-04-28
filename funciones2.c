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

u32 M(u32 a, u32 b, Grafo G)
{
    if (Grado(a, G) < Grado(b, G))
    {
        return -1;
    } else if (Grado(a, G) > Grado(b, G))
    {
        return 1;
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
        printf("Orden Biyectivo\n");
        return(POTENCIA);
    }
    printf("Orden Biyectivo\n");


    // Greedy -----------------------------------
    u32 corMax = 0;
    u32 contador = 0;
    for (size_t i = 0; i < cantVertice; i++)
    {
        bool coloresUsados[cantVertice + 1]; // Array de colores usados
        memset(coloresUsados, false, sizeof(coloresUsados)); // Inicializamos en false

        for (size_t k = 0; k < Grado(Orden[i], G); k++) 
        {                                               
            u32 vecinoID = Vecino(k, Orden[i], G); // id del vecino
            u32 colorVecino = Color(vecinoID, G);
            coloresUsados[colorVecino] = true; // Marcamos el color del vecino como usado
            contador++;
        } 

        // Buscamos el primer color que no esté en uso
        u32 cor = 1;
        while (coloresUsados[cor]) 
        {
            cor++;
            contador++;
        }
        
        AsignarColor(cor, Orden[i], G);

        if (cor > corMax)
        {
            corMax = cor;
        }
        contador++;
    }
    
    printf("Maximo color: %u\n", corMax);
    printf("Numeros lados: %u\n", NumeroDeLados(G));
    printf("Complejidad : %u\n", contador);
 
    return corMax;
}

char GulDukat(Grafo G,u32* Orden) // <!!!> Leer todos los comentarios, Hacete un mate o un cafe <!!!>
{   
    u32 contador = 0; // Es para complejidad
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
        contador++; // <> Es para complejidad
    }
    free(vertColores); // El array solo fue usado para conseguir el color maximo... Era para darle uso a ExtraerColores, para que sirve si no? capaz sirva jajaja
    // REINICIAR CEREBRO, solo conseguimos el color maximo

    u32 divisibles4[cantVertice];
    u32 pares[cantVertice];
    u32 impares[cantVertice];
    u32 size_divisibles4 = 0;
    u32 size_pares = 0;
    u32 size_impares = 0;

    for (u32 cor = 0; cor <= corMax; cor++)
    {
        for (u32 i = 0; i < cantVertice; i++)
        {
            if (Color(i, G) == cor)
            {
                if (cor % 4 == 0)
                {
                    divisibles4[size_divisibles4++] = i;
                    //printf("  Vertice con color divisible por 4: %u\n", i);
                }
                else if (cor % 2 == 0)
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
            contador++; // <> Es para complejidad
        }
    }

    // L E E R  
    // qsort_r esta re bueno, argumentos:
    // ordena el array del primer argumento
    // size es la cantidad de elementos
    // el sizeof es el tamaño de cada elemento
    // el cuarto argumento es la funcion de comparacion, es interesante leerlo! https://en.cppreference.com/w/c/algorithm/qsort
    /*
            comparison function which returns ​a negative integer value if the first argument is less than the second,
            a positive integer value if the first argument is greater than the second and zero if the arguments are equivalent.
    */
    // Quinto elemento exclusivo de la qsort_r, re cheto, le pasa un tercer argumento a la funcion de comparacion
    // Asi podemos pasarle el grafo y hacer todas las funciones del grafo
    qsort_r(divisibles4, size_divisibles4, sizeof(u32), M, G);
    qsort_r(pares, size_pares, sizeof(u32), m, G); // No entendi que es M + m, esto es un placeholder 
    qsort_r(impares, size_impares, sizeof(u32), m, G);

    // Importante: Funciona, orden biyectivo en grafo con mil vertices y ochentamil aristas.
    // Importante: No hay memory leaks
    // Importante: si quieres probar otro grafo, cambiar en el main el tamaño del array de Orden. (consigna!)
    // Importantisimo: Puede que este mal. Dentro de cada array bonito divisibles4 pares impares se ordenan muchos colores viste
    //       Despues de ordenar, dentro de divisibles 4 puede ser id: [0, 5, 6, 7, 8, 9, 44, 12]
    //                                                         color: [4, 8, 4, 4, 8, 8, 16, 8]
    // Osea, queda ordenado por su GRADO, pero no quedan pegaditos sus colores. Creo que tienen que quedar pegaditos


    //printf("A unir los arrays...\n");
    u32 index = 0;
    for (u32 i = 0; i < size_divisibles4; i++) {
        Orden[index++] = divisibles4[i];
        contador++; // <> Es para complejidad
    }
    for (u32 i = 0; i < size_pares; i++) {
        Orden[index++] = pares[i];
        contador++; // <> Es para complejidad
    }
    for (u32 i = 0; i < size_impares; i++) {
        Orden[index++] = impares[i];
        contador++; // <> Es para complejidad
    }


    
    printf("+ Complejidad : %u\n", contador); // <> Es para complejidad 
    return '0'; // si esta bien devuelve esto, consigna
}

char ElimGarak(Grafo G,u32* Orden)
{
    
}