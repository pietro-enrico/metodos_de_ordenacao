#include <stdio.h>
#include "headers/menu.h"

int menuMain(void) {
    // Variáveis do programa
    int opcao;

    //Opções do Menu
    printf("\nOla, seja bem vindo!");
    printf("\nEscolha abaixo o metodo que deseja executar: ");
    printf("\n\n1 - Bubble Sort");
    printf("\n2 - Merge Sort");
    printf("\n3 - Quick Sort");
    printf("\n4 - Exportar resultados");
    printf("\n5 - Sair");

    //Pergunta de escolha ao usuari
    printf("\n\nDigite a opcao desejada: ");
    scanf("%d", &opcao);

    //Respostas do Menu
    switch (opcao) {
        case 1:
            printf("\nMetodo Bubble Sort\n");
            break;

        case 2:
            printf("\nMetodo Merge Sort\n");
            break;

        case 3:
            printf("\nMetodo Quick Sort\n");
            break;

        case 4:
            printf("\nExportando arquivo...\n");
            break;

        case 5:
            printf("\nObrigado por utilizar o programa!!");
            printf("\nFinalizando...");
            break;
        default:
            printf("\nOpcao invalida!");
    }

    return 0;
}
