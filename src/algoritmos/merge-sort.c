#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Intercala as metades já ordenadas array[inicio..meio] e array[meio+1..fim]
static void intercalar(int array[], int auxiliar[], int inicio, int meio, int fim)
{
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    while (i <= meio && j <= fim)
    {
        // "<=" mantém a ordenação estável (iguais preservam a ordem original)
        if (array[i] <= array[j])
        {
            auxiliar[k++] = array[i++];
        }
        else
        {
            auxiliar[k++] = array[j++];
        }
    }

    while (i <= meio)
    {
        auxiliar[k++] = array[i++];
    }

    while (j <= fim)
    {
        auxiliar[k++] = array[j++];
    }

    memcpy(&array[inicio], &auxiliar[inicio], (fim - inicio + 1) * sizeof(int));
}

// Divide recursivamente o intervalo array[inicio..fim] e intercala as metades
static void mergeSortRecursivo(int array[], int auxiliar[], int inicio, int fim)
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
void mergeSort(int array[], int tamanho)
{
    if (array == NULL || tamanho < 2)
    {
        return;
    }

    // Vetor auxiliar alocado uma única vez e reaproveitado em todas as intercalações
    int *auxiliar = (int *)malloc(tamanho * sizeof(int));

    if (auxiliar == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        exit(EXIT_FAILURE);
    }

    mergeSortRecursivo(array, auxiliar, 0, tamanho - 1);

    free(auxiliar);
    auxiliar = NULL;
}
