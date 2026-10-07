
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "headers/array.h"

// Verifica se um número já existe no array
bool numeroExiste(int array[], int tamanho, int numero)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (array[i] == numero)
        {
            return true;
        }
    }

    return false;
}

// Gera um número com uma distribuição melhor de magnitudes (pequenos, médios e grandes)
int gerarNumeroMisto()
{
    int categoria = rand() % 100;

    if (categoria < 30) {
        return rand() % QTD_NUMEROS_PEQUENOS;      // 30% de chance para números pequenos (0 a 999)
    } else if (categoria < 70) {
        return rand() % QTD_NUMEROS_MEDIOS;    // 40% de chance para números médios (0 a 99.999)
    } else {
        return rand() % QTD_NUMEROS_GRANDES;   // 30% de chance para números grandes (0 a 999.999)
    }
}

// Gera um número que ainda não existe no array
int gerarNumeroUnico(int array[], int tamanho)
{
    int numero;

    do
    {
        numero = gerarNumeroMisto();
    }
    while (numeroExiste(array, tamanho, numero));

    return numero;
}

// Função principal de geração
int *gerarArray(int tamanho, bool duplicidade, Disposicao disposicao)
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

    int *array = (int *)malloc(tamanho * sizeof(int));

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
                    array[i] = (tamanho * 20) + (rand() % (tamanho * 5 + 1));
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
            for (int i = 0; i < tamanho; i++)
            {
                if (duplicidade)
                {
                    array[i] = gerarNumeroMisto();
                }
                else
                {
                    array[i] = gerarNumeroUnico(array, i);
                }
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

                array[i] = (int)(formato * 1000000);

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

                array[i] = (int)(formato * 1000000);

                if (duplicidade && i > 0 && rand() % 100 < CHANCE_DUPLICIDADE)
                {
                    array[i] = array[i - 1];
                }
            }

            break;
    }

    return array;
}