#ifndef METODOS_DE_ORDENACAO_MENU_H
#define METODOS_DE_ORDENACAO_MENU_H

#include "array.h"

typedef enum
{
    BUBBLE_SORT,
    MERGE_SORT,
    QUICK_SORT,
} Algoritmo;

typedef struct OpcoesMenu {
    Algoritmo algoritmo;
    int tamanho;
    bool duplicidade;
    Disposicao disposicao;
} OpcoesMenu;

// Algoritmos de Ordenação
long long* bubbleSort(long long array[], int tamanho);
long long* mergeSort(long long array[], int tamanho);
long long* quickSort(long long array[], int tamanho);

int menuMain(void);
void limparTela();

#endif