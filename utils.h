/*
 * ============================================================================
 * utils.h
 * ============================================================================
 * Módulo com funções utilitárias para manipulação de dados e I/O.
 * Inclui leitura de arquivos e escrita de resultados.
 * ============================================================================
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * Estrutura para armazenar estatísticas de execução de um algoritmo.
 */
typedef struct {
    long comparacoes;        // Número total de comparações realizadas
    long trocas;             // Número total de trocas realizadas
    double tempo_ms;         // Tempo de execução em milissegundos
} Estatisticas;

/**
 * Lê números de um arquivo de entrada.
 * 
 * @param nome_arquivo: Caminho do arquivo a ser lido
 * @param array: Ponteiro para o array onde os números serão armazenados
 * @return Número de elementos lidos, ou -1 em caso de erro
 */
int ler_arquivo(const char *nome_arquivo, int **array);

/**
 * Escreve os números ordenados e as estatísticas em um arquivo de saída.
 * 
 * @param nome_arquivo: Caminho do arquivo de saída
 * @param array: Array com os números ordenados
 * @param tamanho: Número de elementos no array
 * @param stats: Estrutura com as estatísticas de execução
 * @return 0 se sucesso, -1 em caso de erro
 */
int escrever_resultado(const char *nome_arquivo, int *array, int tamanho, Estatisticas *stats);

/**
 * Aloca memória para um array de inteiros.
 * 
 * @param tamanho: Número de elementos
 * @return Ponteiro para o array alocado, ou NULL em caso de erro
 */
int *alocar_array(int tamanho);

/**
 * Libera memória alocada para um array.
 * 
 * @param array: Ponteiro para o array a ser liberado
 */
void liberar_array(int *array);

/**
 * Copia o conteúdo de um array para outro.
 * 
 * @param origem: Array de origem
 * @param destino: Array de destino
 * @param tamanho: Número de elementos a copiar
 */
void copiar_array(int *origem, int *destino, int tamanho);

/**
 * Verifica se um array está ordenado em ordem crescente.
 * 
 * @param array: Array a verificar
 * @param tamanho: Número de elementos
 * @return 1 se ordenado, 0 caso contrário
 */
int esta_ordenado(int *array, int tamanho);

#endif
