/*
 * ============================================================================
 * main.c
 * ============================================================================
 * Programa principal que executa um algoritmo de ordenação para uma entrada.
 *
 * Uso:
 *   ./main <arquivo_entrada> <id_algoritmo>
 *
 * Exemplo:
 *   ./main Instâncias/Instâncias/10000_aleatorio.txt 9
 *
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

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
 * Ordem corresponde aos IDs descritos abaixo.
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
static void exibir_uso(const char *nome_programa)
{
    printf("Uso: %s <arquivo_entrada> <id_algoritmo>\n\n", nome_programa);

    printf("Algoritmos disponíveis:\n");
    for (size_t i = 0; i < NUM_ALGORITMOS; i++) {
        printf("  %2d - %s\n", algoritmos[i].id, algoritmos[i].nome);
    }

    printf("\nExemplos:\n");
    printf("  %s Instâncias/Instâncias/10000_aleatorio.txt 1\n", nome_programa);
    printf("  %s Instâncias/Instâncias/10000_ordenado_crescente.txt 9\n", nome_programa);
    printf("  %s Instâncias/Instâncias/1000000_aleatorio.txt 11\n", nome_programa);
}

/**
 * Encontra algoritmo pelo ID.
 */
static Algoritmo *encontrar_algoritmo(int id)
{
    for (size_t i = 0; i < NUM_ALGORITMOS; i++) {
        if (algoritmos[i].id == id) {
            return &algoritmos[i];
        }
    }
    return NULL;
}

/**
 * Converte uma string para inteiro de forma mais segura que atoi.
 */
static int converter_id_algoritmo(const char *texto, int *id)
{
    char *fim = NULL;
    long valor;

    errno = 0;
    valor = strtol(texto, &fim, 10);

    if (errno != 0 || fim == texto || *fim != '\0') {
        return 0;
    }

    if (valor < 1 || valor > 13) {
        return 0;
    }

    *id = (int)valor;
    return 1;
}

/**
 * Função principal.
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        exibir_uso(argv[0]);
        return EXIT_FAILURE;
    }

    const char *arquivo_entrada = argv[1];
    int id_algoritmo = 0;

    if (!converter_id_algoritmo(argv[2], &id_algoritmo)) {
        fprintf(stderr, "Erro: ID de algoritmo inválido ('%s'). Use um número de 1 a 13.\n\n", argv[2]);
        exibir_uso(argv[0]);
        return EXIT_FAILURE;
    }

    Algoritmo *algoritmo = encontrar_algoritmo(id_algoritmo);
    if (algoritmo == NULL) {
        fprintf(stderr, "Erro: ID de algoritmo inválido (%d).\n", id_algoritmo);
        exibir_uso(argv[0]);
        return EXIT_FAILURE;
    }

    printf("================================================================================\n");
    printf("DADOS DO TESTE\n");
    printf("================================================================================\n");
    printf("Input utilizado:       %s\n", arquivo_entrada);
    printf("Algoritmo utilizado:   %d - %s\n", algoritmo->id, algoritmo->nome);
    printf("Arquivo de saída:      saida.txt\n");
    printf("================================================================================\n\n");

    printf("Lendo arquivo de entrada...\n");
    int *array = NULL;
    int tamanho = ler_arquivo(arquivo_entrada, &array);

    if (tamanho < 0) {
        fprintf(stderr, "Erro: Falha ao ler o input utilizado: %s\n", arquivo_entrada);
        return EXIT_FAILURE;
    }

    printf("✓ Arquivo lido com sucesso: %d elementos\n\n", tamanho);

    if (esta_ordenado(array, tamanho)) {
        printf("⚠ Aviso: o input já está ordenado em ordem crescente.\n\n");
    }

    int *array_ordenado = alocar_array(tamanho);
    if (array_ordenado == NULL) {
        liberar_array(array);
        return EXIT_FAILURE;
    }

    copiar_array(array, array_ordenado, tamanho);

    Estatisticas stats;
    stats.comparacoes = 0;
    stats.trocas = 0;
    stats.tempo_ms = 0.0;

    printf("Executando algoritmo %d - %s...\n", algoritmo->id, algoritmo->nome);
    clock_t tempo_inicio = iniciar_cronometro();

    algoritmo->funcao(array_ordenado, tamanho, &stats.comparacoes, &stats.trocas);

    stats.tempo_ms = obter_tempo_decorrido(tempo_inicio);

    printf("✓ Algoritmo concluído\n\n");

    if (!esta_ordenado(array_ordenado, tamanho)) {
        fprintf(stderr, "Erro: Array não foi ordenado corretamente!\n");
        liberar_array(array);
        liberar_array(array_ordenado);
        return EXIT_FAILURE;
    }

    printf("Escrevendo resultado em saida.txt...\n");
    if (escrever_resultado("saida.txt", array_ordenado, tamanho, &stats) != 0) {
        fprintf(stderr, "Erro: Falha ao escrever arquivo de saída.\n");
        liberar_array(array);
        liberar_array(array_ordenado);
        return EXIT_FAILURE;
    }

    printf("✓ Resultado salvo com sucesso\n\n");

    printf("================================================================================\n");
    printf("RESUMO DA EXECUÇÃO\n");
    printf("================================================================================\n");
    printf("Input utilizado:       %s\n", arquivo_entrada);
    printf("Algoritmo utilizado:   %d - %s\n", algoritmo->id, algoritmo->nome);
    printf("Elementos:             %d\n", tamanho);
    printf("Comparações:           %ld\n", stats.comparacoes);
    printf("Trocas:                %ld\n", stats.trocas);
    printf("Tempo (ms):            %.2f\n", stats.tempo_ms);
    printf("Tempo (s):             %.4f\n", stats.tempo_ms / 1000.0);
    printf("Arquivo de saída:      saida.txt\n");
    printf("================================================================================\n\n");

    liberar_array(array);
    liberar_array(array_ordenado);

    printf("✓ Execução concluída com sucesso!\n");
    return EXIT_SUCCESS;
}