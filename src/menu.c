#include <stdio.h>
#include <stdlib.h>

#include "headers/menu.h"

int menuMain(void) {
    // Variáveis do programa
    OpcoesMenu *opcoesMenu = (OpcoesMenu *) malloc(sizeof(OpcoesMenu));

    if (opcoesMenu == NULL) {
        printf("\nErro ao alocar memoria");
        return 1;
    }

    // Opções do Menu
    system("cls");
    printf("\nOla, seja bem vindo!");
    printf("\nEscolha abaixo o metodo que deseja executar: ");
    printf("\n\n[1] - Bubble Sort");
    printf("\n[2] - Merge Sort");
    printf("\n[3] - Quick Sort");
    printf("\n[4] - Sair");


    //Pergunta de escolha ao usuari
    printf("\n\n> Digite a opcao desejada: ");

    int opcao;
    if (scanf("%d", &opcao) != 1) {
        printf("\nOpcao invalida!");
        free(opcoesMenu);
        return 1;
    }

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
            break;
        default:
            printf("\nOpcao invalida!");
            printf("\nFinalizando...");
    }
    return 0;
}
