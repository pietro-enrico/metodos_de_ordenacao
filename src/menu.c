#include <stdio.h>
#include <stdlib.h>

#include "headers/menu.h"

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

int menuPasso1(OpcoesMenu *opcoesMenu) {
    // Passo 1

    // Opções do Menu
    printf("\nOlá, seja bem vindo!");
    printf("\n[PASSO 1] Escolha abaixo o Método que deseja executar: ");
    printf("\n\n[1] - Bubble Sort");
    printf("\n[2] - Merge Sort");
    printf("\n[3] - Quick Sort");
    printf("\n[4] - Sair");

    validarEntrada();

    //Respostas do Menu
    switch (opcao) {
        case 1:
            printf("\nMetodo Bubble Sort\n");
            opcoesMenu->algoritmo = BUBBLE_SORT;
            break;
        case 2:
            printf("\nMetodo Merge Sort\n");
            opcoesMenu->algoritmo = MERGE_SORT;
            break;
        case 3:
            printf("\nMetodo Quick Sort\n");
            opcoesMenu->algoritmo = QUICK_SORT;
            break;
        case 4:
            printf("\nObrigado por utilizar o programa!!");
            printf("\nFinalizando...");
            return 0;
        default:
            printf("\nOpcao invalida!");
            printf("\nFinalizando...");
            return 0;
    }

    return 2;
}

int menuPasso2(OpcoesMenu *opcoesMenu) {
    // Passo 2

    printf("\n[PASSO 2] Escolha o tamanho do array a se testar: ");
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
            printf("\nDigite o tamanho especifico de array que deseja criar: ");
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

    printf("\n[PASSO 3] Criar array com duplicidade de números? (15%%): ");
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

    printf("\n[PASSO 4] Selecione agora a disposição de como o array será criado: ");
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

    // TODO - Gerar array e utilizar algoritmo de ordenação (ainda a se fazer) no qual foi escolhido para a execução da análise + temporizador

    int *array = gerarArray(opcoesMenu->tamanho, opcoesMenu->duplicidade, opcoesMenu->disposicao);

    printf("[\n");
    for (int i = 0; i < opcoesMenu->tamanho; i++) {
        printf("%d", array[i]);

        if (i < opcoesMenu->tamanho - 1) {
            printf(", ");
        }
        printf("\n");
    }

    printf("]\n");

    free(array);
    free(opcoesMenu);
    return 0;
}

int menuMain(void) {
    // Variáveis do programa
    OpcoesMenu *opcoesMenu = malloc(sizeof(OpcoesMenu));

    if (opcoesMenu == NULL) {
        printf("\nErro ao alocar memoria");
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
    return 0;
}