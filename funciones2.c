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

u32 m(Grafo G)
{
    
    return 0;
}

u32 M(Grafo G, color ColorComp)
{
    u32 VerID;
    u32 gradoMax = 0;
    // hay que guardar el vertice con el mayor grado
    for(u32 i = 0 ; i < NumeroDeVertices(G); i++){
        if (Color(i,G) == ColorComp && gradoMax < Grado(i,G)){
            gradoMax = Grado(i,G); 
            VerID = i; 
        }
    }
    return gradoMax;
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
    u32 cor; // color en portugues jejrejrjejrej
    u32 corMax = 0;
    color colores[cantVertice]; // Array de colores
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

char GulDukat(Grafo G,u32* Orden)
{   
    // Es una idea nomas
    u32 cantVertice = NumeroDeVertices(G);
    color *vertColores = malloc(NumeroDeVertices(G) * sizeof(color));
    if (vertColores == NULL)
    {
        return '1';
    }
    // idea:     
    ExtraerColores(G, vertColores);
    u32 corMax;
    // Consigo la cantidad de colores de manera horrible
    for (size_t i = 0; i < cantVertice; i++)
    {
        if (corMax < vertColores[i])
        {
            corMax = vertColores[i];
        }
    }
    
    for (u32 cor = 1; cor <= corMax; cor++)
    {
        if (cor % 4 == 0) // 
        {
            // u32 divisibles4[cantVertice];
            // M(divisibles4, G); 
            // Ordenar ese array
        }
        else if (cor % 2 == 0)
        {
            // u32 pares[cantVertice];
            // Ordenar ese array
        } else {
            // u32 impares[cantVertice];
            // Ordenar ese array
        }
    }
    // Concatenar esos tres arrays, cada uno ordenado a su manera, resultado final ordenado como piden. 
    
    free(vertColores);

    return '0';
}