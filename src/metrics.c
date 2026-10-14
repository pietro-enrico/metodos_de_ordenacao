#include <windows.h>
#include "headers/metrics.h"

double iniciarMetrificacao(void) {
    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);

    return 0.0;
}

double finalizarMetrificacao(void) {
    QueryPerformanceCounter(&fim);

    return (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / (double)frequencia.QuadPart;
}