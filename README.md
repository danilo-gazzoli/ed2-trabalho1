# Algoritmos de Ordenação em C

Projeto desenvolvido para a disciplina **Estrutura de Dados II**, com o objetivo de implementar e testar algoritmos de ordenação na linguagem C.

O projeto permite escolher **qual arquivo de entrada** será utilizado e **qual algoritmo de ordenação** será executado, usando um script em Bash chamado:

```bash
escolher_teste.sh
```

Com isso, o usuário não precisa executar o programa `main` diretamente. O script mostra um menu, recebe as escolhas e executa o teste automaticamente.

---

## Estrutura do projeto

```text
projeto/
├── main.c
├── sorts.c
├── sorts.h
├── utils.c
├── utils.h
├── timer.c
├── timer.h
├── escolher_teste.sh
├── README.md
├── saida.txt
└── Instâncias/
    └── Instâncias/
        ├── 10000_aleatorio.txt
        ├── 10000_ordenado_crescente.txt
        ├── 10000_ordenado_decrescente.txt
        ├── 1000000_aleatorio.txt
        ├── 1000000_ordenado_crescente.txt
        └── 1000000_ordenado_decrescente.txt
```

---

## Como executar o projeto

Abra o terminal na pasta principal do projeto e execute:

```bash
bash escolher_teste.sh 
```

ou:

```bash
sh escolher_teste.sh
```

O script irá:

1. Compilar o projeto em C.
2. Mostrar os arquivos de entrada disponíveis.
3. Pedir para escolher o ID do input.
4. Mostrar os algoritmos disponíveis.
5. Pedir para escolher o ID do algoritmo.
6. Executar o algoritmo escolhido com o input escolhido.
7. Gerar o arquivo `saida.txt`.

---

## Exemplo de uso

Execute:

```bash
bash escolher_teste.sh
```

O programa mostrará os inputs disponíveis:

```text
INPUTS DISPONÍVEIS:
--------------------------------------------------------------------------------
1 - Instâncias/Instâncias/10000_aleatorio.txt
2 - Instâncias/Instâncias/10000_ordenado_crescente.txt
3 - Instâncias/Instâncias/10000_ordenado_decrescente.txt
4 - Instâncias/Instâncias/1000000_aleatorio.txt
5 - Instâncias/Instâncias/1000000_ordenado_crescente.txt
6 - Instâncias/Instâncias/1000000_ordenado_decrescente.txt
--------------------------------------------------------------------------------
```

Depois, escolha o ID do input:

```text
Escolha o ID do input: 1
```

Em seguida, o script mostrará os algoritmos disponíveis:

```text
ALGORITMOS DISPONÍVEIS:
--------------------------------------------------------------------------------
1 - Bubble Sort
2 - Bubble Sort Otimizado
3 - Insertion Sort Direto
4 - Insertion Sort Binário
5 - Insertion Sort Ternário
6 - Selection Sort
7 - Shell Sort
8 - Heap Sort
9 - QuickSort Centro
10 - QuickSort Mediana de 3
11 - Merge Sort
12 - Radix Sort
13 - Bucket Sort
--------------------------------------------------------------------------------
```

Depois, escolha o ID do algoritmo:

```text
Escolha o ID do algoritmo: 9
```

Nesse exemplo, será executado:

```text
Input escolhido:      Instâncias/Instâncias/10000_aleatorio.txt
Algoritmo escolhido:  9 - QuickSort Centro
```

Caso queira efetuar os testes de maneira mais rápida e eficiente, é possível passar o ID de cada input e algoritmo como parâmetro no comando ```bash escolher_teste.sh ``` para realizar a execução diretamente:

```bash
bash escolher_teste.sh {ID input} {ID algoritmo}
```


---

## Inputs disponíveis

| ID | Arquivo | Descrição |
|---:|---|---|
| 1 | `Instâncias/Instâncias/10000_aleatorio.txt` | 10.000 números em ordem aleatória |
| 2 | `Instâncias/Instâncias/10000_ordenado_crescente.txt` | 10.000 números em ordem crescente |
| 3 | `Instâncias/Instâncias/10000_ordenado_decrescente.txt` | 10.000 números em ordem decrescente |
| 4 | `Instâncias/Instâncias/1000000_aleatorio.txt` | 1.000.000 números em ordem aleatória |
| 5 | `Instâncias/Instâncias/1000000_ordenado_crescente.txt` | 1.000.000 números em ordem crescente |
| 6 | `Instâncias/Instâncias/1000000_ordenado_decrescente.txt` | 1.000.000 números em ordem decrescente |

---

## Algoritmos disponíveis

| ID | Algoritmo | Tipo | Complexidade esperada |
|---:|---|---|---|
| 1 | Bubble Sort | Comparativo simples | O(n²) |
| 2 | Bubble Sort Otimizado | Comparativo simples | O(n) no melhor caso e O(n²) no pior caso |
| 3 | Insertion Sort Direto | Comparativo simples | O(n²) |
| 4 | Insertion Sort Binário | Comparativo simples | O(n²) |
| 5 | Insertion Sort Ternário | Comparativo simples | O(n²) |
| 6 | Selection Sort | Comparativo simples | O(n²) |
| 7 | Shell Sort | Comparativo | Depende da sequência de gaps |
| 8 | Heap Sort | Comparativo avançado | O(n log n) |
| 9 | QuickSort Centro | Comparativo avançado | O(n log n) médio |
| 10 | QuickSort Mediana de 3 | Comparativo avançado | O(n log n) médio |
| 11 | Merge Sort | Comparativo avançado | O(n log n) |
| 12 | Radix Sort | Não comparativo | O(d × n) |
| 13 | Bucket Sort | Não comparativo | O(n + k) médio |

---

## O que o script faz

O arquivo `escolher_teste.sh` é responsável por controlar a execução do projeto.

Ele primeiro compila o código com o comando:

```bash
gcc -Wall -Wextra -O3 -std=c99 *.c -lm -o main
```

Depois, ele apresenta os menus para escolha do input e do algoritmo.

Ao final, o script chama o programa principal internamente, usando o arquivo e o algoritmo escolhidos.

Ou seja, o usuário executa apenas:

```bash
bash escolher_teste.sh
```

E o script cuida do restante.

---

## Saída no terminal

Durante a execução, o programa mostra as informações principais do teste realizado.

Exemplo:

```text
================================================================================
TESTE ESCOLHIDO
================================================================================
Input escolhido:      Instâncias/Instâncias/10000_aleatorio.txt
Algoritmo escolhido:  9 - QuickSort Centro
================================================================================
```

Depois da execução, o programa também mostra um resumo com:

```text
Input utilizado
Algoritmo utilizado
Quantidade de elementos
Número de comparações
Número de trocas
Tempo de execução
Arquivo de saída
```

---

## Arquivo de saída

A cada execução, será criado ou sobrescrito o arquivo:

```text
saida.txt
```

Esse arquivo contém:

1. Os números ordenados, um por linha.
2. O número total de comparações.
3. O número total de trocas.
4. O tempo de execução do algoritmo.

Formato esperado:

```text
<número ordenado 1>
<número ordenado 2>
<número ordenado 3>
...
<comparações>
<trocas>
<tempo em ms>
```

Exemplo simplificado:

```text
1
2
3
4
5
120
40
0.35
```

---

## Atenção sobre algoritmos lentos

Alguns algoritmos possuem complexidade O(n²), como:

```text
Bubble Sort
Bubble Sort Otimizado
Insertion Sort Direto
Insertion Sort Binário
Insertion Sort Ternário
Selection Sort
```

Por isso, eles podem demorar muito quando usados com arquivos grandes, principalmente os de 1.000.000 elementos.

Para testar entradas grandes, recomenda-se usar algoritmos mais eficientes, como:

```text
Heap Sort
QuickSort Centro
QuickSort Mediana de 3
Merge Sort
Radix Sort
```

---

## Módulos do projeto

### `main.c`

Arquivo principal do programa.

Responsável por:

- Receber o arquivo de entrada.
- Receber o algoritmo escolhido.
- Ler os dados do arquivo.
- Executar o algoritmo de ordenação.
- Contar comparações e trocas.
- Medir o tempo de execução.
- Gerar o arquivo `saida.txt`.
- Exibir o resumo da execução no terminal.

### `sorts.c` e `sorts.h`

Contêm a implementação e a declaração dos algoritmos de ordenação.

Algoritmos implementados:

- Bubble Sort
- Bubble Sort Otimizado
- Insertion Sort Direto
- Insertion Sort Binário
- Insertion Sort Ternário
- Selection Sort
- Shell Sort
- Heap Sort
- QuickSort Centro
- QuickSort Mediana de 3
- Merge Sort
- Radix Sort
- Bucket Sort

### `utils.c` e `utils.h`

Contêm funções auxiliares para:

- Ler arquivos de entrada.
- Alocar memória.
- Copiar arrays.
- Verificar se o array está ordenado.
- Escrever o arquivo `saida.txt`.

### `timer.c` e `timer.h`

Contêm funções para medir o tempo de execução dos algoritmos.

### `escolher_teste.sh`

Script usado para escolher o input e o algoritmo que serão executados.

Ele é o comando principal de uso do projeto.

---

## Resumo rápido

Para executar o projeto, use:

```bash
bash escolher_teste.sh
```

Depois escolha:

```text
ID do input
ID do algoritmo
```

O programa executará o teste escolhido e gerará o arquivo:

```text
saida.txt
```

---

## Observação final

O projeto foi organizado para facilitar os testes individuais dos algoritmos de ordenação a fim de analisar a performance de cada algoritmo para cada input.