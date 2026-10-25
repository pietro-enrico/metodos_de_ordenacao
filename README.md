# Métodos de Ordenação em C

Este projeto foi desenvolvido para estudar e comparar diferentes algoritmos de ordenação utilizando a linguagem C.

A proposta é implementar os algoritmos, testar seu comportamento com diferentes conjuntos de dados e registrar métricas de execução para entender melhor suas diferenças de desempenho.

## Sobre o projeto

O projeto reúne três algoritmos de ordenação:

- **Bubble Sort (em desenvolvimento):** compara elementos adjacentes e realiza trocas até que o array esteja ordenado.
- **Merge Sort:** divide o array em partes menores, ordena essas partes e depois as combina.
- **Quick Sort:** utiliza um pivô para particionar o array e ordenar seus elementos recursivamente.

Além da implementação dos algoritmos, o programa permite configurar os dados utilizados nos testes e registrar os resultados de cada execução.

## Funcionalidades

- Menu interativo no terminal, organizado em quatro passos.
- Geração de arrays de números inteiros (`long long`) com tamanho configurável.
- Opção de gerar o array com ou sem números duplicados.
- Cinco disposições de dados: crescente, decrescente, aleatória, côncava e convexa.
- Medição do tempo de execução com temporizador de alta precisão.
- Contagem de comparações, movimentações e trocas realizadas por cada algoritmo.
- Exportação automática das métricas para um arquivo CSV compatível com o Excel.

## Tecnologias utilizadas

- **Linguagem:** C (padrão C11)
- **Build:** CMake
- **Compilador:** GCC (MinGW)
- **Ambiente de desenvolvimento:** CLion
- **Bibliotecas:** apenas a biblioteca padrão da linguagem C e a API do Windows (Win32). Nenhuma biblioteca de terceiros é utilizada.

### Uso da biblioteca padrão e da API do Windows

| Recurso | Origem | Finalidade |
|---|---|---|
| `fprintf`, `fputs` (`stdio.h`) | Biblioteca padrão C | Escrita dos registros no arquivo CSV |
| `time`, `strftime` (`time.h`) | Biblioteca padrão C | Data e hora de cada execução |
| `QueryPerformanceCounter` | API do Windows | Medição do tempo de execução com alta precisão |
| `SetConsoleOutputCP`, `SetConsoleCP` | API do Windows | Exibição e leitura de acentos no terminal (UTF-8) |
| `MultiByteToWideChar` | API do Windows | Conversão do caminho do arquivo para UTF-16, permitindo pastas com acentos e espaços |
| `CreateDirectoryW` | API do Windows | Criação automática da pasta de resultados |
| `_wfopen` | Runtime C da Microsoft | Abertura do arquivo CSV com caminho Unicode |

> Por depender da API do Windows, o projeto deve ser compilado e executado no **Windows**.

## Estrutura do projeto

```text
metodos_de_ordenacao/
├── cmake/                    # Scripts auxiliares do CMake (suporte a caminhos com acentos no MinGW)
├── headers/                  # Arquivos de cabeçalho (.h)
├── src/
│   ├── algoritmos/           # Bubble Sort, Merge Sort e Quick Sort
│   ├── core/                 # Geração dos arrays
│   ├── interface/            # Menu e formatação dos rótulos exibidos
│   └── metricas/             # Medição e exportação das métricas
│       └── resultados/       # Arquivo metricas.csv gerado pelo programa
├── main.c                    # Ponto de entrada do programa
├── CMakeLists.txt            # Configuração da compilação
├── README.md
└── .gitignore
```

## Como executar

### Pré-requisitos

- Windows.
- Um compilador C compatível com o padrão C11, como o GCC do MinGW.
- CMake.
- CLion ou outro ambiente capaz de configurar e compilar projetos C com CMake.

### Compilação

Na raiz do projeto, execute:

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
```

O executável será gerado dentro de `cmake-build-debug/`, com o nome `metodos_de_ordenacao.exe`.

Caso o projeto esteja em uma pasta cujo caminho tenha acentos, o CMake ajusta os caminhos automaticamente para que o MinGW consiga compilar.

### Configuração do terminal no CLion

Para que o programa interaja corretamente com o usuário pelo console, habilite a opção **Emulate terminal in the output console**:

1. Na barra superior do CLion, abra o menu de configurações da execução, clicando nos três pontos (`⁝`) ao lado da configuração atual.
2. Selecione **Edit**.
3. Na janela **Run/Debug Configurations**, localize a configuração `metodos_de_ordenacao`.
4. Marque a opção **Emulate terminal in the output console**.
5. Clique em **Apply** e depois em **OK**.

Essa configuração permite emular um terminal na janela de saída do CLion, o que é necessário para o menu interativo e a entrada de dados pelo teclado.

### Execução pelo terminal

No PowerShell, execute:

```powershell
.\cmake-build-debug\metodos_de_ordenacao.exe
```

Se estiver utilizando o CLion, você também pode carregar o projeto pelo `CMakeLists.txt` e executá-lo pela própria IDE.

## Utilização

Ao iniciar, o programa conduz o usuário por quatro passos:

1. **Algoritmo:** Bubble Sort, Merge Sort ou Quick Sort.
2. **Tamanho do array:** 1.000, 5.000, 10.000, 100.000 ou um valor personalizado.
3. **Duplicidade:** gerar o array com ou sem números repetidos.
4. **Disposição:** crescente, decrescente, aleatória, côncava ou convexa.

Em seguida, o array é gerado e ordenado. O programa exibe o array ordenado, as configurações escolhidas e as métricas da execução, que também são gravadas no arquivo CSV.

## Métricas coletadas

| Métrica | Descrição |
|---|---|
| **Tempo de execução** | Tempo gasto apenas na ordenação, em milissegundos, medido com `QueryPerformanceCounter` |
| **Comparações** | Quantidade de comparações entre elementos do array |
| **Movimentações** | Quantidade de escritas de elementos em posições do array ou de arrays auxiliares |
| **Trocas** | No Quick Sort, quantidade de vezes em que dois elementos trocaram de posição. No Merge Sort, como não há troca direta, conta as vezes em que um elemento da metade direita é posicionado antes dos elementos restantes da metade esquerda |

A geração do array não entra na medição: a contagem começa imediatamente antes da chamada do algoritmo e termina logo após a ordenação.

## Registro das métricas

A cada execução, o programa acrescenta uma linha ao arquivo:

```text
src/metricas/resultados/metricas.csv
```

A pasta e o arquivo são criados automaticamente na primeira execução. As execuções seguintes são adicionadas ao final do arquivo, formando um histórico para comparação.

O CSV possui as seguintes colunas:

```text
Data/Hora;Algoritmo;Quantidade de Números;Duplicidade;Disposição;Tempo (ms);Comparações;Movimentações;Trocas
```

Exemplo de registro:

```text
18/10/2026 14:04:54;Merge Sort;1000;Sim;Crescente;0,0790;5044;19952;0
```

Para abrir diretamente no Excel em português, o arquivo é gerado com:

- codificação **UTF-8 com BOM**, para exibir os acentos corretamente;
- **ponto e vírgula** (`;`) como separador de colunas;
- **vírgula** como separador decimal.

O arquivo também pode ser aberto no LibreOffice Calc ou em outros programas compatíveis com CSV.

## Objetivo acadêmico

Mais do que implementar algoritmos conhecidos, este projeto busca compreender como diferentes estratégias de ordenação se comportam na prática.

Ao variar o tamanho, a duplicidade e a disposição dos dados, é possível observar diferenças de desempenho e relacioná-las à lógica e à complexidade de cada algoritmo.

## Autores

- R583970 — Fernanda Brezolino Neves Gomes
- F3623A6 — José Henrique Lima Alves
- H7642E0 — Matheus Almeida Aguirra
- R8475H1 — Pietro Enrico Fernandes Silva

Projeto desenvolvido como parte dos estudos de programação em linguagem C, com foco em algoritmos, estruturas de dados e análise de desempenho.
