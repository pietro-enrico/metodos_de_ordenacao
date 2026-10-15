#ifndef METODOS_DE_ORDENACAO_EXPORT_H
#define METODOS_DE_ORDENACAO_EXPORT_H

#include "menu.h"
#include "metrics.h"

// Diretório raiz do repositório (definido pelo CMake), usado para salvar as métricas exportadas
#ifndef DIRETORIO_PROJETO
#define DIRETORIO_PROJETO "."
#endif

#define DIRETORIO_RESULTADOS DIRETORIO_PROJETO "/resultados"
#define ARQUIVO_METRICAS DIRETORIO_RESULTADOS "/metricas.csv"

int exportarMetricas(const OpcoesMenu *opcoesMenu, Metricas metricas);

#endif //METODOS_DE_ORDENACAO_EXPORT_H
