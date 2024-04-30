#include "APIG24.h"

#define POTENCIA 4294967295U

struct ArrayConTamaño {
    u32 *arr;
    u32 size;
};

struct argumentos {
    u32 *arr;
    Grafo grafo;
};

u32 Greedy(Grafo G,u32* Orden);

char GulDukat(Grafo G,u32* Orden);

char ElimGarak(Grafo G,u32* Orden);

bool checkOrden(u32 size, u32* Orden);

int CompareColor(const void *a, const void *b, void *arg);

u32 minGrado(u32* array_de_ids, u32 size_de_ese_array, Grafo G);

u32 maxGrado(u32* array_de_ids, u32 size_de_ese_array, Grafo G);

u32 m(struct ArrayConTamaño *a, struct ArrayConTamaño *b, Grafo G);

u32 M(struct ArrayConTamaño *a, struct ArrayConTamaño *b, Grafo G);

u32 M_m(struct ArrayConTamaño *a, struct ArrayConTamaño *b, Grafo G);

