#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "exportacao.h"
#include "formatacao-rotulos.h"

// Formata o double com vírgula decimal (padrão do Excel em português)
static void formatarDecimal(char *destino, size_t capacidade, double valor) {
    snprintf(destino, capacidade, "%.4f", valor);

    for (char *c = destino; *c != '\0'; c++) {
        if (*c == '.') {
            *c = ',';
        }
    }
}

static int converterCaminho(const char *origem, wchar_t *destino, int capacidade) {
    int resultado = MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS, origem,-1, destino,capacidade);

    return resultado != 0;
}

// Acrescenta uma linha com as métricas da ordenação no CSV (abre direto no Excel)
// Retorna 1 em caso de sucesso e 0 em caso de erro
    int exportarMetricas(const OpcoesMenu *opcoesMenu, Metricas metricas) {
    wchar_t diretorio[MAX_PATH];
    wchar_t caminhoArquivo[MAX_PATH];

    if (!converterCaminho(DIRETORIO_RESULTADOS, diretorio, MAX_PATH) ||
      !converterCaminho(ARQUIVO_METRICAS, caminhoArquivo, MAX_PATH)) {
        printf("Erro ao converter o caminho para UTF-16.\n");
        return 0;
      }

    if (!CreateDirectoryW(diretorio, NULL)) {
        DWORD erro = GetLastError();

        if (erro != ERROR_ALREADY_EXISTS) {
            printf("Erro ao criar diretorio: %lu\n", erro);
            return 0;
        }
    }

    FILE *arquivo = _wfopen(caminhoArquivo, L"ab");

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
