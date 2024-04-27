#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "EstructuraGrafo24.h"
#include "APIG24.h"

#define POTENCIA 4294967295U

void agregar_vecino(Grafo grafo, u32 v, u32 ve){
    if(grafo->vertices[v].grado == 0){
        grafo->vertices[v].grado = 1;
        grafo->vertices[v].vecinos = calloc(1, sizeof(u32));
        grafo->vertices[v].color = 0;
        grafo->vertices[v].vecinos[0] = ve;
    } else if (grafo->vertices[v].grado != 0) {
        grafo->vertices[v].grado += 1;
        grafo->vertices[v].vecinos = realloc(grafo->vertices[v].vecinos,(grafo->vertices[v].grado)*sizeof(u32));
        grafo->vertices[v].vecinos[grafo->vertices[v].grado - 1] = ve;
        if (grafo->delta < grafo->vertices[v].grado){
            grafo->delta = grafo->vertices[v].grado;
        }
    }
}
// Funcion auxiliar para agregar vecinos a un vertice
void agregar_vecinos(Grafo grafo, u32 v1, u32 v2){
    agregar_vecino(grafo, v1, v2);
    agregar_vecino(grafo, v2, v1);
}

Grafo ConstruirGrafo(){
    // Inicializo el grafo y le aloco memoria
    Grafo grafo = (Grafo)malloc(sizeof(struct GrafoSt)); // Aloco memoria para el grafo
    if(grafo == NULL){ // Si no se pudo alocar memoria
        return NULL; // Retorno NULL
    }
    grafo->cant_vertices = 0; // Inicializo la cantidad de vertices en 0
    grafo->cant_lados = 0; // Inicializo la cantidad de lados en 0
    grafo->delta = 0; // Inicializo el delta en 0

    // Leo la cantidad de vertices y lados
    u32 cant_vert = 0, cant_aristas = 0; // Inicio las variables en 0
    char line[1024]; // Creo un buffer para leer la linea de stdin
    while (fgets(line, sizeof(line), stdin)) // Mientras pueda leer una linea de stdin
    {
        if (line[0] == 'c') {
            continue; // Si la linea empieza con 'c' sigo leyendo
        }
        
        if (line[0] == 'p') // Si la linea empieza con 'p'
        {
            sscanf(line, "p edge %d %d", &cant_vert, &cant_aristas); // Leo la cantidad de vertices y lados
            break; // Salgo del while
        }
    }

    if (cant_vert == 0 || cant_aristas == 0) // Si no se pudo leer la cantidad de vertices o lados
    {
        free(grafo); // Libero la memoria del grafo
        return NULL; // Retorno NULL
    }
    
    grafo->cant_vertices = cant_vert; // Asigno la cantidad de vertices al grafo
    grafo->cant_lados = cant_aristas; // Asigno la cantidad de lados al grafo

    // Voy a ir cargando los vertices y lados en el grafo, pero primero tengo que alocar memoria para los vertices y lados
    grafo->vertices = (struct Vertice*)malloc(cant_vert * sizeof(struct Vertice)); // Aloco memoria para los vertices
    if(grafo->vertices == NULL){ // Si no se pudo alocar memoria
        free(grafo->vertices); // Libero la memoria de los vertices
        free(grafo); // Libero la memoria del grafo
        return NULL; // Retorno NULL
    }
    // Inicializo los vertices para evitar errores de memoria
    for (u32 i = 0; i < cant_vert; i++) {
        grafo->vertices[i].grado = 0;
        grafo->vertices[i].vecinos = NULL;
        grafo->vertices[i].color = 0;
    }
    // Ahora voy a cargar los vertices y lados en el grafo, hacemos un while para ir leyendo y llamamos a la funcion new_vertice
    while(fgets(line, sizeof(line), stdin)){ // Mientras pueda leer una linea de stdin
        if (line[0] == 'c') {
            continue; // Si la linea empieza con 'c' sigo leyendo
        }
        if (line[0] == 'e') // Si la linea empieza con 'e'
        {
            u32 v1 = 0, v2 = 0; // Inicializo las variables en 0
            sscanf(line, "e %d %d", &v1, &v2); // Leo los vertices de la arista
            agregar_vecinos(grafo, v1, v2);
        }
    }
    return grafo; // Retorno el grafo
}

void DestruccionDelVertice(struct Vertice vertice){
    free(vertice.vecinos);
}

void DestruirGrafo(Grafo G){
    for(u32 i = 0; i < G->cant_vertices; i++){
        DestruccionDelVertice(G->vertices[i]);
    }
    free(G->vertices);
    free(G);
}

// Funciones para sacar informacion
u32 NumeroDeVertices(Grafo G){
    return G->cant_vertices;
}

u32 NumeroDeLados(Grafo G)
{
    return G->cant_lados; 
}


u32 Delta(Grafo G)
{
    return G->delta; 
}

u32 Grado(u32 i,Grafo G){
    if(i >= G->cant_vertices){
        return 0;
    }
    u32 res = G->vertices[i].grado;
    return res;
}

color Color(u32 i,Grafo G){
    if(i < G->cant_vertices){
        color res = G->vertices[i].color;
        return res;
    } else {
        return POTENCIA; // Investigar como hacer potencias en C dios mio dios mio
    }
}

u32 Vecino(u32 j,u32 i,Grafo G){
    //if(i >= G->cant_vertices || (i < G->cant_vertices) ^ (j >= Grado(i,G))){
    //    return POTENCIA;
    // }
    u32 id_vecino = G->vertices[i].vecinos[j];
    return id_vecino;
}

void AsignarColor(color x,u32 i,Grafo  G){
    if(i <= G->cant_vertices){
        G->vertices[i].color = x;
    }
}

void ExtraerColores(Grafo G,color* Color){
    for(u32 i = 0 ; i < G->cant_vertices ; i++){ //entre 0 y n-1
        Color[i] = G->vertices[i].color;
    }
}

void ImportarColores(color* Color,Grafo  G){
    for(u32 i = 0 ; i < G->cant_vertices ; i++){ //entre 0 y n-1
        G->vertices[i].color = Color[i];
    }
}