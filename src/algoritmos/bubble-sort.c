#include "metricas.h"
#include <stdio.h>
#include <stdlib.h>

long long* bubbleSort(long long array[], int tamanho)
{
    if (array == NULL || tamanho < 2)
    {
        return array;
    }

    for (int fim = tamanho - 1; fim > 0; fim--)
    {
        int houveTroca = 0;

        for (int i = 0; i < fim; i++)
        {
            registrarComparacao();

            if (array[i] > array[i + 1])
            {
                long long temporario = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temporario;

                registrarTroca();
                registrarMovimentacao(3);
                houveTroca = 1;
            }
        }

        /* Se nenhuma troca ocorreu, o array já está ordenado. */
        if (!houveTroca)
        {
            break;
        }
    }

    return array;
}