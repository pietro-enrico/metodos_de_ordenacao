#include "metricas.h"

// Trocar valores de variáveis passadas através de ponteiros - Mudança na memória
void trocar(long long* x, long long* y) {
    long long temporaria = *x;
    *x = *y;
    *y = temporaria;

    registrarMovimentacao(2);
    registrarTroca();
}

// Encontrar o elemento mediano do array e retorná-lo para ser o pivô
long long medianaDeTres(long long array[], long long inicio, long long fim) {
    long long meio = inicio + (fim - inicio) / 2;

    if ((array[inicio] >= array[meio] && array[inicio] <= array[fim]) ||
        (array[inicio] <= array[meio] && array[inicio] >= array[fim])) {
        return inicio;
    }

    if ((array[meio] >= array[inicio] && array[meio] <= array[fim]) ||
        (array[meio] <= array[inicio] && array[meio] >= array[fim])) {
        return meio;
    }

    return fim;
}

// Particionamento de Hoare - Encontrando a mediana para tentar equilibrar a divisão dos subconjuntos
long long particionamento(long long array[], long long inicio, long long fim) {
    long long posicaoPivo = medianaDeTres(array, inicio, fim);
    long long pivo = array[posicaoPivo];

    long long i = inicio - 1;
    long long j = fim + 1;

    while (1) {
        for (i++; array[i] < pivo; i++) {
            registrarComparacao();
        }
        registrarComparacao();

        for (j--; array[j] > pivo; j--) {
            registrarComparacao();
        }
        registrarComparacao();

        registrarComparacao();
        if (i >= j) return j;
        trocar(&array[i], &array[j]);
    }
}

// Separa as partições dos subconjuntos e chama a recursividade
static void quickSortRecursivo(long long array[], long long inicio, long long fim) {
    if (inicio >= fim) return;

    long long particao = particionamento(array, inicio, fim);

    quickSortRecursivo(array, inicio, particao);
    quickSortRecursivo(array, particao + 1, fim);
}

// Função Principal que faz o EntryPoint
long long* quickSort(long long array[], int tamanho) {
    if (tamanho <= 1) return array;

    quickSortRecursivo(array, 0, tamanho - 1);
    return array;
}
