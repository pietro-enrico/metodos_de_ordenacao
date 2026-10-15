#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "headers/menu.h"
#include "headers/labels-filters.h"
#include "headers/metrics.h"
#include "headers/export.h"

static int opcao;

static int validarEntrada() {
    opcao = 0;
    //Pergunta de escolha ao usuario
    printf("\n\n> Digite a opção desejada: ");
    if (scanf("%d", &opcao) != 1) {
        printf("\nOpção Inválida!");
        exit(1);
    }
    return 1;
}

void limparTela() {
    system("@cls || clear");
}

static void imprimirArrayOrdenado(const long long * array, int tamanho_array) {
    limparTela();

    size_t capacidade = (size_t)tamanho_array * 24 + 4;
    char *buffer = malloc(capacidade);

    if (buffer == NULL)
    {
        printf("Erro ao alocar memoria para impressao.\n");
        return;
    }

    size_t posicao = 0;

    posicao += snprintf(buffer + posicao, capacidade - posicao, "[ ");

    for (int i = 0; i < tamanho_array; i++)
    {
        posicao += snprintf(
            buffer + posicao,
            capacidade - posicao,
            "%lld%s",
            array[i],
            i < tamanho_array - 1 ? ", " : " "
        );
    }

    posicao += snprintf(
    buffer + posicao,
    capacidade - posicao,
    "]\n");

    fwrite(buffer, 1, posicao, stdout);

    free(buffer);
    buffer = NULL;
}

int menuPasso1(OpcoesMenu *opcoesMenu) {
    // Passo 1
    limparTela();

    // Opções do Menu
    printf("Olá, seja bem vindo!");
    printf("\n[PASSO 1] Escolha abaixo o Método de Ordenação que deseja executar: ");
    printf("\n\n[1] - Bubble Sort");
    printf("\n[2] - Merge Sort");
    printf("\n[3] - Quick Sort");
    printf("\n[4] - Sair");

    validarEntrada();

    //Respostas do Menu
    switch (opcao) {
        case 1:
            opcoesMenu->algoritmo = BUBBLE_SORT;
            break;
        case 2:
            opcoesMenu->algoritmo = MERGE_SORT;
            break;
        case 3:
            opcoesMenu->algoritmo = QUICK_SORT;
            break;
        case 4:
            printf("\nObrigado por utilizar o programa!!");
            printf("\nFinalizando...");
            return 0;
        default:
            printf("\nOpção Inválida!");
            printf("\nFinalizando...");
            return 0;
    }

    return 2;
}

int menuPasso2(OpcoesMenu *opcoesMenu) {
    // Passo 2
    limparTela();

    printf("[PASSO 2] Escolha o tamanho do array a se testar: ");
    printf("\n\n[1] - 1000");
    printf("\n[2] - 5000");
    printf("\n[3] - 10000");
    printf("\n[4] - 100000");
    printf("\n[5] - Outro");

    validarEntrada();

    // Respostas do Menu
    switch (opcao) {
        case 1:
            opcoesMenu->tamanho = 1000;
            break;
        case 2:
            opcoesMenu->tamanho = 5000;
            break;
        case 3:
            opcoesMenu->tamanho = 10000;
            break;
        case 4:
            opcoesMenu->tamanho = 100000;
            break;
        case 5:
            int tamanho;
            printf("\n> Digite o tamanho específico de array que deseja gerar: ");
            if (scanf("%d", &tamanho) != 1) {
                printf("\nOpção Inválida!");
                exit(1);
            }

            opcoesMenu->tamanho = tamanho;
            break;
        default:
            printf("\nOpção Inválida!");
            printf("\nFinalizando...");
            return 0;
    }

    return 3;
}

int menuPasso3(OpcoesMenu *opcoesMenu) {
    // Passo 3
    limparTela();

    printf("[PASSO 3] Criar array com duplicidade de números? (15%%): ");
    printf("\n\n[1] - Sim");
    printf("\n[2] - Não");

    validarEntrada();

    switch (opcao) {
        case 1:
            opcoesMenu->duplicidade = true;
            break;
        case 2:
            opcoesMenu->duplicidade = false;
            break;
        default:
            printf("\nOpção Inválida!");
            printf("\nFinalizando...");
            return 0;
    }
    return 4;
}

int menuPasso4(OpcoesMenu *opcoesMenu) {
    // Passo 4
    limparTela();

    printf("[PASSO 4] Selecione agora a disposição de como o array será criado: ");
    printf("\n\n[1] - CRESCENTE");
    printf("\n[2] - DECRESCENTE");
    printf("\n[3] - ALEATÓRIO");
    printf("\n[4] - CÔNCAVA");
    printf("\n[5] - CONVEXA");

    validarEntrada();

    switch (opcao) {
        case 1:
            opcoesMenu->disposicao = CRESCENTE;
            break;
        case 2:
            opcoesMenu->disposicao = DECRESCENTE;
            break;
        case 3:
            opcoesMenu->disposicao = ALEATORIO;
            break;
        case 4:
            opcoesMenu->disposicao = CONCAVA;
            break;
        case 5:
            opcoesMenu->disposicao = CONVEXA;
            break;
        default:
            printf("\nOpção Inválida!");
            printf("\nFinalizando...");
            return 0;
    }

    long long *array = gerarArray(opcoesMenu->tamanho, opcoesMenu->duplicidade, opcoesMenu->disposicao);

    // Métrica: mede a quantidade de operações realizadas para ordernar e o tempo de execução do algoritmo de ordenação
    iniciarMetrificacao();

    switch (opcoesMenu->algoritmo) {
        case BUBBLE_SORT:
            array = bubbleSort(array, opcoesMenu->tamanho);
            break;
        case MERGE_SORT:
            array = mergeSort(array, opcoesMenu->tamanho);
            break;
        case QUICK_SORT:
            array = quickSort(array, opcoesMenu->tamanho);
            break;
    }

    finalizarMetrificacao();
    imprimirArrayOrdenado(array, opcoesMenu->tamanho);

    printf("\nAlgoritmo: %s", formatarLabelAlgoritmo(opcoesMenu->algoritmo));
    printf("\nQuantidade de Números: %d", opcoesMenu->tamanho);
    printf("\nDuplicidade: %s", formatarLabelDuplicidade(opcoesMenu->duplicidade));
    printf("\nDisposição: %s", formatarLabelDisposicao(opcoesMenu->disposicao));

    Metricas metricas = obterMetricas();

    printf("\n\n========= MÉTRICAS DE ORDENAÇÃO =========\n");
    printf("\nTempo de execução: %.4f ms (%.6f s)", metricas.tempoDecorridoMs, metricas.tempoDecorridoMs / 1000.0);
    printf("\nQuantidade de Comparações: %llu", metricas.comparacoes);
    printf("\nQuantidade de Movimentações: %llu", metricas.movimentacoes);
    printf("\nQuantidade de Trocas: %llu\n", metricas.trocas);

    if (exportarMetricas(opcoesMenu, metricas)) {
        printf("\nMétricas exportadas para: %s\n", ARQUIVO_METRICAS);
    }

    free(array);
    array = NULL;

    return 0;
}

int menuMain(void) {
    // Variáveis do programa
    OpcoesMenu *opcoesMenu = malloc(sizeof(OpcoesMenu));

    if (opcoesMenu == NULL) {
        printf("\nErro ao alocar memória");
        free(opcoesMenu);
        return 1;
    }

    int passo = 1;

    while (passo != 0) {
        switch (passo) {
            case 1:
                passo = menuPasso1(opcoesMenu);
                break;
            case 2:
                passo = menuPasso2(opcoesMenu);
                break;
            case 3:
                passo = menuPasso3(opcoesMenu);
                break;
            case 4:
                passo = menuPasso4(opcoesMenu);
                break;
            default:
                passo = 0;
                break;
        }
    }

    free(opcoesMenu);
    opcoesMenu = NULL;

    return 0;
}