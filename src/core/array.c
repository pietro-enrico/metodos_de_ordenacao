#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "array.h"

// Gera um inteiro aleatório de 30 bits (no MinGW o RAND_MAX é 32767, apenas 15 bits)
static long long randLargo()
{
    return ((long long)(rand() & 0x7FFF) << 15) | (rand() & 0x7FFF);
}

// Gera um número com uma distribuição melhor de magnitudes (pequenos, médios e grandes)
long long gerarNumeroMisto()
{
    int categoria = rand() % 100;

    if (categoria < 30) {
        return randLargo() % QTD_NUMEROS_PEQUENOS;      // 30% de chance para números pequenos (0 a 999)
    } else if (categoria < 70) {
        return randLargo() % QTD_NUMEROS_MEDIOS;    // 40% de chance para números médios (0 a 99.999)
    } else {
        return randLargo() % QTD_NUMEROS_GRANDES;   // 30% de chance para números grandes (0 a 999.999)
    }
}

// Preenche o array com números únicos em ordem aleatória - O(n), sem busca por repetidos
static void gerarNumerosUnicos(long long array[], int tamanho)
{
    // Valores distintos por construção: cada um é maior que o anterior
    array[0] = rand() % 100;

    for (int i = 1; i < tamanho; i++)
    {
        array[i] = array[i - 1] + (rand() % 20 + 1);
    }

    // Embaralhamento de Fisher-Yates
    for (int i = tamanho - 1; i > 0; i--)
    {
        int j = (int)(randLargo() % (i + 1));

        long long temporaria = array[i];
        array[i] = array[j];
        array[j] = temporaria;
    }
}

// Função principal de geração
long long *gerarArray(int tamanho, bool duplicidade, Disposicao disposicao)
{
    static bool inicializado = false;

    // Inicializa o gerador apenas uma vez
    if (!inicializado)
    {
        srand((unsigned)time(NULL));
        inicializado = true;
    }

    if (tamanho <= 0)
    {
        printf("Tamanho invalido.\n");
        exit(EXIT_FAILURE);
    }

    long long *array = (long long *)malloc(tamanho * sizeof(long long));

    if (array == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        exit(EXIT_FAILURE);
    }

    switch (disposicao)
    {
        case CRESCENTE:
            for (int i = 0; i < tamanho; i++)
            {
                if (i == 0)
                {
                    array[i] = rand() % 100;
                }
                else
                {
                    int incremento = rand() % 20 + 1;

                    // Permite duplicidade ocasional
                    if (duplicidade && rand() % 100 < CHANCE_DUPLICIDADE)
                    {
                        array[i] = array[i - 1];
                    }
                    else
                    {
                        array[i] = array[i - 1] + incremento;
                    }
                }
            }

            break;

        case DECRESCENTE:
            for (int i = 0; i < tamanho; i++)
            {
                if (i == 0)
                {
                    // INSTEAD OF: array[i] = tamanho * 20;
                    // Add some randomness to the starting value for the descending array
                    // so it's not always the exact same sequence.
                    array[i] = ((long long)tamanho * 20) + (rand() % (tamanho * 5 + 1));
                }
                else
                {
                    int decremento = rand() % 20 + 1;

                    if (duplicidade && rand() % 100 < CHANCE_DUPLICIDADE)
                    {
                        array[i] = array[i - 1];
                    }
                    else
                    {
                        array[i] = array[i - 1] - decremento;
                    }
                }
            }

            break;

        case ALEATORIO:
            if (duplicidade)
            {
                for (int i = 0; i < tamanho; i++)
                {
                    array[i] = gerarNumeroMisto();
                }
            }
            else
            {
                gerarNumerosUnicos(array, tamanho);
            }

            break;

        case CONCAVA:
            for (int i = 0; i < tamanho; i++)
            {
                double x;

                if (tamanho == 1)
                {
                    x = 0.5;
                }
                else
                {
                    x = (double)i / (tamanho - 1);
                }

                // 0 -> 1.000.000 -> 0
                double formato = 4.0 * x * (1.0 - x);

                array[i] = (long long)(formato * 1000000);

                if (duplicidade && i > 0 && rand() % 100 < CHANCE_DUPLICIDADE)
                {
                    array[i] = array[i - 1];
                }
            }

            break;

        case CONVEXA:
            for (int i = 0; i < tamanho; i++)
            {
                double x;

                if (tamanho == 1)
                {
                    x = 0.5;
                }
                else
                {
                    x = (double)i / (tamanho - 1);
                }

                // 1.000.000 -> 0 -> 1.000.000
                double formato = 4.0 * (x - 0.5) * (x - 0.5);

                array[i] = (long long)(formato * 1000000);

                if (duplicidade && i > 0 && rand() % 100 < CHANCE_DUPLICIDADE)
                {
                    array[i] = array[i - 1];
                }
            }

            break;
    }

    return array;
}