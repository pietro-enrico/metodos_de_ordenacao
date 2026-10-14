#include <windows.h>
#include "headers/metrics.h"

static LARGE_INTEGER frequencia, inicio, fim;
static Metricas metricas;

void iniciarMetrificacao(void) {
    metricas.comparacoes = 0;
    metricas.movimentacoes = 0;
    metricas.trocas = 0;
    metricas.tempoDecorridoMs = 0;

    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);
}

void finalizarMetrificacao(void) {
    QueryPerformanceCounter(&fim);

    metricas.tempoDecorridoMs = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / (double)frequencia.QuadPart;
}

void registrarComparacao(void) {
    metricas.comparacoes++;
}

void registrarMovimentacao(unsigned long long quantidade) {
    metricas.movimentacoes += quantidade;
}

void registrarTroca(void) {
    metricas.trocas++;
}

Metricas obterMetricas(void) {
    return metricas;
};
