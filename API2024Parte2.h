#include "APIG24.h"

struct ArrayConTamaño {
    u32 *arr;
    u32 size;
};

u32 Greedy(Grafo G,u32* Orden);

char GulDukat(Grafo G,u32* Orden);

char ElimGarak(Grafo G,u32* Orden);

bool checkOrden(u32 size, u32* Orden);

u32 minGrado(u32* array_de_ids, u32 size_de_ese_array, Grafo G);

u32 maxGrado(u32* array_de_ids, u32 size_de_ese_array, Grafo G);

u32 m(struct ArrayConTamaño *a, struct ArrayConTamaño *b, Grafo G);

u32 M(struct ArrayConTamaño *a, struct ArrayConTamaño *b, Grafo G);

u32 M_m(struct ArrayConTamaño *a, struct ArrayConTamaño *b, Grafo G);

