#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../headers/metrics.h"

// Intercala as metades já ordenadas array[inicio..meio] e array[meio+1..fim]
static void intercalar(long long array[], long long auxiliar[], int inicio, int meio, int fim)
{
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    while (i <= meio && j <= fim)
    {
        registrarComparacao();
        // "<=" mantém a ordenação estável (iguais preservam a ordem original)
        if (array[i] <= array[j])
        {
            auxiliar[k++] = array[i++];
        }
        else
        {
            // Elemento da metade direita passa na frente da esquerda: conta como troca de posição
            auxiliar[k++] = array[j++];
            registrarTroca();
        }
        registrarMovimentacao(1);
    }

    while (i <= meio)
    {
        auxiliar[k++] = array[i++];
        registrarMovimentacao(1);
    }

    while (j <= fim)
    {
        auxiliar[k++] = array[j++];
        registrarMovimentacao(1);
    }

    memcpy(&array[inicio], &auxiliar[inicio], (fim - inicio + 1) * sizeof(long long));

    registrarMovimentacao((unsigned long long)(fim - inicio + 1));
}

// Divide recursivamente o intervalo array[inicio..fim] e intercala as metades
static void mergeSortRecursivo(long long array[], long long auxiliar[], int inicio, int fim)
{
    if (inicio >= fim)
    {
        return;
    }

    int meio = inicio + (fim - inicio) / 2;

    mergeSortRecursivo(array, auxiliar, inicio, meio);
    mergeSortRecursivo(array, auxiliar, meio + 1, fim);
    intercalar(array, auxiliar, inicio, meio, fim);
}

// Ordena o array recebido do menu (in-place, em ordem crescente)
long long* mergeSort(long long array[], int tamanho)
{
    if (array == NULL || tamanho < 2)
    {
        return array;
    }

    // Vetor auxiliar alocado uma única vez e reaproveitado em todas as intercalações
    long long *auxiliar = (long long *) malloc(tamanho * sizeof(long long));

    if (auxiliar == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        exit(EXIT_FAILURE);
    }

    mergeSortRecursivo(array, auxiliar, 0, tamanho - 1);

    free(auxiliar);
    auxiliar = NULL;

    return array;
}
