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

int menuMain(void);
void limparTela();

#endif