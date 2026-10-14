#include <bemapiset.h>

#include "headers/menu.h"
#include "headers/labels-filters.h"

const char* formatarLabelAlgoritmo(Algoritmo tipo_algoritmo) {
    switch (tipo_algoritmo) {
        case BUBBLE_SORT:
            return "Bubble Sort";
            break;
        case MERGE_SORT:
            return "Merge Sort";
            break;
        case QUICK_SORT:
            return "Quick Sort";
            break;
        default:
            return "Algortimo Desconhecido";
    }
}

const char* formatarLabelDuplicidade(bool duplicidade) {
    switch ((int)(duplicidade)) {
        case 0:
            return "Não";
            break;
        case 1:
            return "Sim";
            break;
        default:
            return "Desconhecido";
    }
}

const char* formatarLabelDisposicao(Disposicao disposicao) {
    switch (disposicao) {
        case CRESCENTE:
            return "Crescente";
            break;
        case DECRESCENTE:
            return "Decrescente";
            break;
        case ALEATORIO:
            return "Aleatório";
            break;
        case CONCAVA:
            return "Côncava";
            break;
        case CONVEXA:
            return "Convexa";
            break;
        default:
            return "Disposição Desconhecida";
    }
}