/*
 * ============================================================================
 * main.c
 * ============================================================================
 * Programa principal que executa os algoritmos de ordenação.
 * 
 * Uso: main <arquivo_entrada> <algoritmo>
 *      main all
 * 
 * Algoritmos disponíveis:
 *   1 - Bubble Sort
 *   2 - Bubble Sort Otimizado
 *   3 - Insertion Sort (Direto)
 *   4 - Insertion Sort (Binário)
 *   5 - Insertion Sort (Ternário)
 *   6 - Selection Sort
 *   7 - Shell Sort
 *   8 - Heap Sort
 *   9 - QuickSort (Pivô Centro)
 *  10 - QuickSort (Pivô Mediana de 3)
 *  11 - Merge Sort
 *  12 - Radix Sort
 *  13 - Bucket Sort
 * 
 * Opção especial:
 *   all - Executa todos os 13 algoritmos com todos os 6 arquivos (78 testes)
 * 
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sorts.h"
#include "utils.h"
#include "timer.h"

/**
 * Estrutura para armazenar informações sobre um algoritmo de ordenação.
 */
typedef struct {
    int id;                           // ID do algoritmo
    const char *nome;                 // Nome descritivo
    void (*funcao)(int *, int, long *, long *);  // Ponteiro para função
} Algoritmo;

/**
 * Array com todos os algoritmos disponíveis.
 * Ordem corresponde aos IDs descritos acima.
 */
static Algoritmo algoritmos[] = {
    {1, "Bubble Sort", bolha},
    {2, "Bubble Sort Otimizado", bolha_otimizado},
    {3, "Insertion Sort (Direto)", insercao_direta},
    {4, "Insertion Sort (Binário)", insercao_binaria},
    {5, "Insertion Sort (Ternário)", insercao_ternaria},
    {6, "Selection Sort", selecao_direta},
    {7, "Shell Sort", shell_sort},
    {8, "Heap Sort", heap_sort},
    {9, "QuickSort (Centro)", quicksort_centro},
    {10, "QuickSort (Mediana)", quicksort_mediana},
    {11, "Merge Sort", merge_sort},
    {12, "Radix Sort", radix_sort},
    {13, "Bucket Sort", bucket_sort}
};

#define NUM_ALGORITMOS (sizeof(algoritmos) / sizeof(algoritmos[0]))

/**
 * Exibe mensagem de uso.
 */
void exibir_uso(const char *nome_programa)
{
    printf("Uso: %s <arquivo_entrada> <id_algoritmo>\n\n", nome_programa);
    printf("Algoritmos disponíveis (1-13):\n");
    
    for (size_t i = 0; i < NUM_ALGORITMOS; i++) {
        printf("  %2d - %s\n", algoritmos[i].id, algoritmos[i].nome);
    }
    printf("\nExemplos:\n");
    printf("  %s Instâncias/Instâncias/10000_aleatorio.txt 1\n", nome_programa);
    printf("  %s Instâncias/Instâncias/1000000_aleatorio.txt 11\n", nome_programa);
}

/**
 * Encontra algoritmo pelo ID.
 * 
 * @param id: ID do algoritmo
 * @return Ponteiro para estrutura Algoritmo ou NULL se não encontrado
 */
Algoritmo *encontrar_algoritmo(int id)
{
    for (size_t i = 0; i < NUM_ALGORITMOS; i++) {
        if (algoritmos[i].id == id) {
            return &algoritmos[i];
        }
    }
    return NULL;
}

/**
 * Função principal.
 */
int main(int argc, char *argv[])
{
    // Validação de argumentos
    if (argc != 3) {
        exibir_uso(argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *arquivo_entrada = argv[1];
    int id_algoritmo = atoi(argv[2]);
    
    // Encontra o algoritmo
    Algoritmo *algoritmo = encontrar_algoritmo(id_algoritmo);
    if (algoritmo == NULL) {
        fprintf(stderr, "Erro: ID de algoritmo inválido (%d)\n", id_algoritmo);
        exibir_uso(argv[0]);
        return EXIT_FAILURE;
    }
    
    printf("================================================================================\n");
    printf("Algoritmo de Ordenação: %s\n", algoritmo->nome);
    printf("Arquivo de entrada: %s\n", arquivo_entrada);
    printf("================================================================================\n\n");
    
    // Lê arquivo de entrada
    printf("Lendo arquivo de entrada...\n");
    int *array = NULL;
    int tamanho = ler_arquivo(arquivo_entrada, &array);
    
    if (tamanho < 0) {
        fprintf(stderr, "Erro: Falha ao ler arquivo\n");
        return EXIT_FAILURE;
    }
    
    printf("✓ Arquivo lido com sucesso: %d elementos\n\n", tamanho);
    
    // Verifica se já está ordenado
    if (esta_ordenado(array, tamanho)) {
        printf("⚠ Aviso: Array já está ordenado!\n\n");
    }
    
    // Aloca cópia para ordenação
    int *array_ordenado = alocar_array(tamanho);
    if (array_ordenado == NULL) {
        liberar_array(array);
        return EXIT_FAILURE;
    }
    
    copiar_array(array, array_ordenado, tamanho);
    
    // Inicializa estatísticas
    Estatisticas stats;
    stats.comparacoes = 0;
    stats.trocas = 0;
    
    // Inicia cronometragem
    printf("Executando algoritmo...\n");
    clock_t tempo_inicio = iniciar_cronometro();
    
    // Executa o algoritmo de ordenação
    algoritmo->funcao(array_ordenado, tamanho, &stats.comparacoes, &stats.trocas);
    
    // Para cronometragem
    stats.tempo_ms = obter_tempo_decorrido(tempo_inicio);
    
    printf("✓ Algoritmo concluído\n\n");
    
    // Valida resultado
    if (!esta_ordenado(array_ordenado, tamanho)) {
        fprintf(stderr, "Erro: Array não foi ordenado corretamente!\n");
        liberar_array(array);
        liberar_array(array_ordenado);
        return EXIT_FAILURE;
    }
    
    // Escreve resultado
    printf("Escrevendo resultado em saida.txt...\n");
    if (escrever_resultado("saida.txt", array_ordenado, tamanho, &stats) != 0) {
        fprintf(stderr, "Erro: Falha ao escrever arquivo de saída\n");
        liberar_array(array);
        liberar_array(array_ordenado);
        return EXIT_FAILURE;
    }
    
    printf("✓ Resultado salvo com sucesso\n\n");
    
    // Exibe estatísticas
    printf("================================================================================\n");
    printf("ESTATÍSTICAS DE EXECUÇÃO\n");
    printf("================================================================================\n");
    printf("Comparações:     %ld\n", stats.comparacoes);
    printf("Trocas:          %ld\n", stats.trocas);
    printf("Tempo (ms):      %.2f\n", stats.tempo_ms);
    printf("Tempo (s):       %.2f\n", stats.tempo_ms / 1000.0);
    printf("================================================================================\n\n");
    
    // Libera memória
    liberar_array(array);
    liberar_array(array_ordenado);
    
    printf("✓ Execução concluída com sucesso!\n");
    return EXIT_SUCCESS;
}
