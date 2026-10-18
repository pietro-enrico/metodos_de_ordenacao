# Métodos de Ordenação em C

Este projeto foi desenvolvido para estudar e comparar diferentes algoritmos de ordenação utilizando a linguagem C.

A proposta é implementar os algoritmos, testar seu comportamento com diferentes conjuntos de dados e registrar métricas de execução para entender melhor suas diferenças de desempenho.

## Sobre o projeto

O projeto reúne três algoritmos de ordenação:

- **Bubble Sort:** compara elementos adjacentes e realiza trocas até que o array esteja ordenado.
- **Merge Sort:** divide o array em partes menores, ordena essas partes e depois as combina.
- **Quick Sort:** utiliza um pivô para particionar o array e ordenar seus elementos recursivamente.

Além da implementação dos algoritmos, o programa permite configurar os dados utilizados nos testes e registrar os resultados das execuções.

## Funcionalidades

- Geração de arrays com diferentes tamanhos e disposições.
- Configuração da presença de elementos duplicados.
- Execução dos algoritmos de ordenação disponíveis.
- Medição do tempo de execução.
- Registro das métricas em um arquivo CSV.
- Organização do código em módulos para facilitar a manutenção e a evolução do projeto.

## Tecnologias utilizadas

- **Linguagem:** C
- **Padrão:** C11
- **Build:** CMake
- **Ambiente de desenvolvimento:** CLion

## Estrutura do projeto

```text
metodos_de_ordenacao/
├── headers/              # Arquivos de cabeçalho
├── src/
│   ├── algoritmos/       # Implementações dos algoritmos
│   ├── core/             # Funcionalidades centrais
│   ├── interface/        # Menu e interação com o usuário
│   └── metricas/         # Medição e exportação dos resultados
├── main.c                # Ponto de entrada do programa
├── CMakeLists.txt        # Configuração da compilação
├── README.md
└── .gitignore
```

Os resultados das execuções são armazenados em um arquivo CSV no diretório configurado para as métricas.

## Como executar

### Pré-requisitos

Antes de começar, você precisa ter instalado:

- Um compilador C compatível com o padrão C11, como GCC ou MinGW.
- CMake.
- CLion ou outro ambiente capaz de configurar e compilar projetos C com CMake.

### Compilação

Na raiz do projeto, execute:

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
```

No Windows, o executável normalmente será gerado dentro de `cmake-build-debug/`, com o nome `metodos_de_ordenacao.exe`.

### Configuração do terminal no CLion

Para que o programa interaja corretamente com o usuário pelo console, habilite a opção **Emulate terminal in the output console**:

1. Na barra superior do CLion, abra o menu de configurações da execução, clicando nos três pontos (`⁝`) ao lado da configuração atual.
2. Selecione **Edit**.
3. Na janela **Run/Debug Configurations**, localize a configuração `metodos_de_ordenacao`.
4. Marque a opção **Emulate terminal in the output console**.
5. Clique em **Apply** e depois em **OK**.

Essa configuração permite emular um terminal na janela de saída do CLion, o que pode ser útil para programas que utilizam menus interativos e entrada de dados pelo teclado.

### Execução pelo terminal

No PowerShell, execute:

```powershell
.\cmake-build-debug\metodos_de_ordenacao.exe
```

Se estiver utilizando o CLion, você também pode carregar o projeto pelo `CMakeLists.txt` e executá-lo pela própria IDE.

## Registro das métricas

Durante os testes, o programa registra os resultados em um arquivo CSV, permitindo consultar e comparar as execuções posteriormente.

O arquivo pode ser aberto em ferramentas como Excel, LibreOffice Calc ou outros programas compatíveis com CSV.

Para garantir que os resultados sejam salvos corretamente, o diretório de destino precisa existir e o programa deve ter permissão para gravar nele.

## Objetivo acadêmico

Mais do que implementar algoritmos conhecidos, este projeto busca compreender como diferentes estratégias de ordenação se comportam na prática.

Ao variar o tamanho e a disposição dos dados, é possível observar diferenças de desempenho e relacioná-las à lógica de cada algoritmo.

## Autores

- R583970 — Fernanda Brezolino Neves Gomes
- F3623A6 — José Henrique Lima Alves
- H7642E0 — Matheus Almeida Aguirra
- R8475H1 — Pietro Enrico Fernandes Silva

Projeto desenvolvido como parte dos estudos de programação em linguagem C, com foco em algoritmos, estruturas de dados e análise de desempenho.