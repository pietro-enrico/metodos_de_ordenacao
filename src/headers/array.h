#ifndef METODOS_DE_ORDENACAO_ARRAY_H
#define METODOS_DE_ORDENACAO_ARRAY_H
#include <stdbool.h>

// Chance (em %) de repetir o valor anterior nas disposições CRESCENTE e DECRESCENTE
#define CHANCE_DUPLICIDADE 10

#define QTD_NUMEROS_PEQUENOS 1000
#define QTD_NUMEROS_MEDIOS 100000
#define QTD_NUMEROS_GRANDES 1000000

typedef enum
{
    CRESCENTE,
    DECRESCENTE,
    ALEATORIO,
    CONCAVA,
    CONVEXA
} Disposicao;

int *gerarArray(int tamanho, bool duplicidade, Disposicao disposicao);

#endif //METODOS_DE_ORDENACAO_ARRAY_H
