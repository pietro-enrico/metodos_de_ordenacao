#ifndef METODOS_DE_ORDENACAO_METRICS_H
#define METODOS_DE_ORDENACAO_METRICS_H

typedef struct Metricas
{
    unsigned long long comparacoes;
    unsigned long long movimentacoes;
    unsigned long long trocas;
    double tempoDecorridoMs;
} Metricas;

void iniciarMetrificacao(void);
void finalizarMetrificacao(void);

void registrarComparacao(void);
void registrarMovimentacao(unsigned long long quantidade);
void registrarTroca(void);

Metricas obterMetricas(void);

#endif //METODOS_DE_ORDENACAO_METRICS_H
