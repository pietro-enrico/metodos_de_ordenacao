#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "headers/export.h"
#include "headers/labels-filters.h"

// Formata o double com vírgula decimal (padrão do Excel em português)
static void formatarDecimal(char *destino, size_t capacidade, double valor) {
    snprintf(destino, capacidade, "%.4f", valor);

    for (char *c = destino; *c != '\0'; c++) {
        if (*c == '.') {
            *c = ',';
        }
    }
}

// Acrescenta uma linha com as métricas da ordenação no CSV (abre direto no Excel)
// Retorna 1 em caso de sucesso e 0 em caso de erro
int exportarMetricas(const OpcoesMenu *opcoesMenu, Metricas metricas) {
    CreateDirectoryA(DIRETORIO_RESULTADOS, NULL);

    FILE *arquivo = fopen(ARQUIVO_METRICAS, "ab");

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo de métricas: %s\n", ARQUIVO_METRICAS);
        return 0;
    }

    // Arquivo novo: escreve o BOM UTF-8 (para o Excel exibir os acentos) e o cabeçalho
    fseek(arquivo, 0, SEEK_END);
    if (ftell(arquivo) == 0) {
        fputs("\xEF\xBB\xBF", arquivo);
        fputs("Data/Hora;Algoritmo;Quantidade de Números;Duplicidade;Disposição;"
              "Tempo (ms);Comparações;Movimentações;Trocas\r\n", arquivo);
    }

    time_t agora = time(NULL);
    char dataHora[20];
    strftime(dataHora, sizeof(dataHora), "%d/%m/%Y %H:%M:%S", localtime(&agora));

    char tempoMs[32];
    formatarDecimal(tempoMs, sizeof(tempoMs), metricas.tempoDecorridoMs);

    fprintf(arquivo, "%s;%s;%d;%s;%s;%s;%llu;%llu;%llu\r\n",
            dataHora,
            formatarLabelAlgoritmo(opcoesMenu->algoritmo),
            opcoesMenu->tamanho,
            formatarLabelDuplicidade(opcoesMenu->duplicidade),
            formatarLabelDisposicao(opcoesMenu->disposicao),
            tempoMs,
            metricas.comparacoes,
            metricas.movimentacoes,
            metricas.trocas);

    fclose(arquivo);
    arquivo = NULL;

    return 1;
}
