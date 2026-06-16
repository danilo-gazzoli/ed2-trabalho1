# Algoritmos de Ordenação em C

## 🚀 COMO USAR

### Compilar

```bash
gcc -Wall -Wextra -O3 -std=c99 -lm *.c -o main
```

### Executar um Algoritmo

```bash
./main Instâncias/Instâncias/10000_aleatorio.txt 1
```

### Executar TODOS os Algoritmos (78 testes)

Para rodar todos os 13 algoritmos com todos os 6 arquivos:

```bash
bash run_all.sh
```

---

## 📚 Algoritmos (13 Total)

| ID | Nome | Tipo | Complexidade |
|----|------|------|--------------|
| 1 | Bubble Sort | Simples | O(n²) |
| 2 | Bubble Otimizado | Simples | O(n)-O(n²) |
| 3 | Insertion Direto | Simples | O(n²) |
| 4 | Insertion Binário | Simples | O(n²) |
| 5 | Insertion Ternário | Simples | O(n²) |
| 6 | Selection Sort | Simples | O(n²) |
| 7 | Shell Sort | Simples | ~O(n^1.3) |
| 8 | Heap Sort | Avançado | O(n log n) |
| 9 | QuickSort Centro | Avançado | O(n log n) |
| 10 | QuickSort Mediana | Avançado | O(n log n) |
| 11 | Merge Sort | Avançado | O(n log n) |
| 12 | Radix Sort | Não-Comp | O(d*n) |
| 13 | Bucket Sort | Não-Comp | O(n+k) |

---

## 💻 Exemplos de Uso

```bash
# 10mil elementos aleatórios com Merge Sort (ID 11)
./main Instâncias/Instâncias/10000_aleatorio.txt 11

# 1 milhão de elementos com Radix Sort (ID 12)
./main Instâncias/Instâncias/1000000_aleatorio.txt 12

# 10mil já ordenado com Bubble Sort (ID 1)
./main Instâncias/Instâncias/10000_ordenado_crescente.txt 1

# Executar todos os 78 testes e gerar tabela
bash run_all.sh
```

---

## ⚡ Executar Todos os Testes

Para executar todos os 13 algoritmos com todos os 6 arquivos de dados (78 testes total):

```bash
bash run_all.sh
```

Isso vai:
- Compilar automaticamente se necessário
- Rodar todos os 78 testes
- Exibir uma tabela com comparações, trocas e tempo de cada teste
- Mostrar um resumo final

**Requisitos**: bash (disponível em Linux, macOS, Git Bash no Windows, ou WSL no Windows)



## 📁 Estrutura

```
projeto/
├── *.c, *.h      (Código-fonte dos 13 algoritmos)
├── run_all.sh    (Script para executar todos os testes)
├── README.md     (Este arquivo)
├── Instâncias/   (6 arquivos de dados)
└── saida.txt     (Resultado da última execução)
```

---

## ⏱️ Tempos Esperados

**10.000 elementos:**
- Bubble Sort: ~100ms
- Merge Sort: ~3ms  
- Radix Sort: ~1ms

**1.000.000 elementos:**
- O(n log n): ~300ms
- O(n²): Não teste (muito lento)

---

## 📊 Saída

Cada teste gera `saida.txt`:

```
<números ordenados>
<comparações>
<trocas>
<tempo em ms>
```

---

## ✅ Resumo

**Simples e Direto:**
1. Compile: `gcc -Wall -Wextra -O3 -std=c99 -lm *.c -o main`
2. Teste 1: `./main Instâncias/Instâncias/10000_aleatorio.txt 1`
3. Teste Todos: `bash run_all.sh`

**Pronto!** 🎉
