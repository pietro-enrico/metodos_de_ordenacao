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

void bubbleSort(int array[], int tamanho);
void mergeSort(int array[], int tamanho);
void quickSort(int array[], int tamanho);

int menuMain(void);
void limparTela();

#endif