/*
 * ============================================================================
 * utils.c
 * ============================================================================
 * Implementação do módulo utilitário.
 * ============================================================================
 */

#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ler_arquivo(const char *nome_arquivo, int **array)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo '%s'\n", nome_arquivo);
        return -1;
    }
    
    // Contagem inicial de números para alocação de memória
    int tamanho = 0;
    int num_temp;
    
    // Primeiro pass: contar quantos números existem
    while (fscanf(arquivo, "%d", &num_temp) == 1) {
        tamanho++;
    }
    
    // Volta ao início do arquivo para leitura dos dados
    rewind(arquivo);
    
    // Aloca memória para o array
    *array = (int *)malloc(tamanho * sizeof(int));
    if (*array == NULL) {
        fprintf(stderr, "Erro: Não foi possível alocar memória\n");
        fclose(arquivo);
        return -1;
    }
    
    // Lê os números do arquivo
    for (int i = 0; i < tamanho; i++) {
        if (fscanf(arquivo, "%d", &(*array)[i]) != 1) {
            fprintf(stderr, "Erro: Falha na leitura do arquivo\n");
            fclose(arquivo);
            free(*array);
            return -1;
        }
    }
    
    fclose(arquivo);
    return tamanho;
}

int escrever_resultado(const char *nome_arquivo, int *array, int tamanho, Estatisticas *stats)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída '%s'\n", nome_arquivo);
        return -1;
    }
    
    // Escreve os números ordenados
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n", array[i]);
    }
    
    // Escreve as estatísticas
    fprintf(arquivo, "%ld\n", stats->comparacoes);
    fprintf(arquivo, "%ld\n", stats->trocas);
    fprintf(arquivo, "%.2f\n", stats->tempo_ms);
    
    fclose(arquivo);
    return 0;
}

int *alocar_array(int tamanho)
{
    int *array = (int *)malloc(tamanho * sizeof(int));
    
    if (array == NULL) {
        fprintf(stderr, "Erro: Não foi possível alocar memória para array de tamanho %d\n", tamanho);
    }
    
    return array;
}

void liberar_array(int *array)
{
    if (array != NULL) {
        free(array);
    }
}

void copiar_array(int *origem, int *destino, int tamanho)
{
    for (int i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

int esta_ordenado(int *array, int tamanho)
{
    for (int i = 1; i < tamanho; i++) {
        if (array[i] < array[i - 1]) {
            return 0;
        }
    }
    return 1;
}
