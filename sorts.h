/*
 * ============================================================================
 * sorts.h
 * ============================================================================
 * Módulo contendo a declaração de todos os 13+ algoritmos de ordenação.
 * Cada algoritmo implementa a assinatura padrão:
 *   void algoritmo(int *array, int tamanho, long *comparacoes, long *trocas)
 * ============================================================================
 */

#ifndef SORTS_H
#define SORTS_H

/* ========== ALGORITMOS SIMPLES DE ORDENAÇÃO ========== */

/**
 * Bubble Sort (Ordenação por Bolha)
 * Compara elementos adjacentes e troca se estiverem na ordem errada.
 * Complexidade: O(n²) em todos os casos
 * 
 * @param array: Array a ser ordenado
 * @param tamanho: Número de elementos
 * @param comparacoes: Ponteiro para contador de comparações
 * @param trocas: Ponteiro para contador de trocas
 */
void bolha(int *array, int tamanho, long *comparacoes, long *trocas);

/**
 * Bubble Sort com Critério de Parada
 * Versão otimizada do bubble sort que detecta quando o array está ordenado.
 * Complexidade: O(n²) pior caso, O(n) melhor caso
 */
void bolha_otimizado(int *array, int tamanho, long *comparacoes, long *trocas);

/**
 * Insertion Sort (Ordenação por Inserção Direta)
 * Insere cada elemento na sua posição correta no subarray ordenado.
 * Complexidade: O(n²) em todos os casos
 */
void insercao_direta(int *array, int tamanho, long *comparacoes, long *trocas);

/**
 * Insertion Sort com Busca Binária
 * Utiliza busca binária para encontrar a posição de inserção.
 * Reduz comparações, mas trocas continuam O(n²)
 * Complexidade: O(n²) no pior caso
 */
void insercao_binaria(int *array, int tamanho, long *comparacoes, long *trocas);

/**
 * Insertion Sort com Busca Ternária
 * Utiliza busca ternária para encontrar a posição de inserção.
 * Similar à busca binária, com variação no número de comparações
 * Complexidade: O(n²) no pior caso
 */
void insercao_ternaria(int *array, int tamanho, long *comparacoes, long *trocas);

/**
 * Selection Sort (Ordenação por Seleção Direta)
 * Encontra o elemento mínimo e coloca na posição correta.
 * Complexidade: O(n²) em todos os casos
 */
void selecao_direta(int *array, int tamanho, long *comparacoes, long *trocas);

/**
 * Shell Sort
 * Generalização do insertion sort com gaps decrescentes.
 * Complexidade: Depende da sequência de gaps, aprox. O(n log n) no melhor caso
 */
void shell_sort(int *array, int tamanho, long *comparacoes, long *trocas);

/* ========== ALGORITMOS AVANÇADOS DE ORDENAÇÃO ========== */

/**
 * Heap Sort
 * Utiliza uma heap (árvore binária) para ordenar elementos.
 * Complexidade: O(n log n) em todos os casos
 */
void heap_sort(int *array, int tamanho, long *comparacoes, long *trocas);

/**
 * Quick Sort com Pivô no Centro
 * Particiona o array usando o elemento central como pivô.
 * Complexidade: O(n log n) em média, O(n²) no pior caso
 */
void quicksort_centro(int *array, int tamanho, long *comparacoes, long *trocas);

/**
 * Quick Sort com Pivô pela Mediana de 3
 * Escolhe o pivô pela mediana entre primeiro, central e último elementos.
 * Estratégia melhor para evitar pior caso.
 * Complexidade: O(n log n) em média, O(n²) no pior caso
 */
void quicksort_mediana(int *array, int tamanho, long *comparacoes, long *trocas);

/**
 * Merge Sort
 * Algoritmo de divisão e conquista que divide o array e mescla.
 * Complexidade: O(n log n) em todos os casos
 * Espaço: O(n) para array auxiliar
 */
void merge_sort(int *array, int tamanho, long *comparacoes, long *trocas);

/* ========== ALGORITMOS NÃO-COMPARATIVOS ========== */

/**
 * Radix Sort
 * Ordena números inteiros usando dígitos individuais.
 * Assume números não-negativos
 * Complexidade: O(d * n) onde d é número de dígitos
 */
void radix_sort(int *array, int tamanho, long *comparacoes, long *trocas);

/**
 * Bucket Sort
 * Distribui elementos em buckets e ordena cada bucket.
 * Funciona bem com números em intervalo conhecido.
 * Complexidade: O(n + k) em média, onde k é número de buckets
 */
void bucket_sort(int *array, int tamanho, long *comparacoes, long *trocas);

#endif
