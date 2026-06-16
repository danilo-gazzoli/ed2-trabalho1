/*
 * ============================================================================
 * sorts.c
 * ============================================================================
 * Implementação de 13 algoritmos de ordenação (14 variações).
 * Todos contam comparações e trocas conforme especificado.
 * ============================================================================
 */

#include "sorts.h"
#include <stdlib.h>
#include <string.h>

/* ========== FUNÇÕES AUXILIARES ========== */

/**
 * Troca dois elementos do array.
 * Incrementa o contador de trocas.
 */
static inline void trocar(int *a, int *b, long *trocas)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    (*trocas)++;
}

/**
 * Compara dois elementos.
 * Incrementa o contador de comparações.
 * 
 * @return -1 se a < b, 0 se a == b, 1 se a > b
 */
static inline int comparar(int a, int b, long *comparacoes)
{
    (*comparacoes)++;
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

/* ========== ALGORITMOS SIMPLES ========== */

void bolha(int *array, int tamanho, long *comparacoes, long *trocas)
{
    // Externa: percorre o array tamanho-1 vezes
    for (int i = 0; i < tamanho - 1; i++) {
        
        // Interna: compara elementos adjacentes
        // Reduz o intervalo a cada iteração pois maiores sobem ao final
        for (int j = 0; j < tamanho - 1 - i; j++) {
            
            // Compara par de elementos adjacentes
            if (comparar(array[j], array[j + 1], comparacoes) > 0) {
                trocar(&array[j], &array[j + 1], trocas);
            }
        }
    }
}

void bolha_otimizado(int *array, int tamanho, long *comparacoes, long *trocas)
{
    // Flag para detectar se houve trocas nesta iteração
    int houve_troca;
    
    for (int i = 0; i < tamanho - 1; i++) {
        houve_troca = 0;
        
        for (int j = 0; j < tamanho - 1 - i; j++) {
            if (comparar(array[j], array[j + 1], comparacoes) > 0) {
                trocar(&array[j], &array[j + 1], trocas);
                houve_troca = 1;
            }
        }
        
        // Se nenhuma troca ocorreu, o array está ordenado
        if (!houve_troca) {
            break;
        }
    }
}

void insercao_direta(int *array, int tamanho, long *comparacoes, long *trocas)
{
    // Começa do segundo elemento (índice 1)
    for (int i = 1; i < tamanho; i++) {
        int chave = array[i];
        int j = i - 1;
        
        // Move elementos maiores que a chave uma posição para frente
        while (j >= 0 && comparar(array[j], chave, comparacoes) > 0) {
            array[j + 1] = array[j];
            (*trocas)++;  // Conta deslocamento como troca
            j--;
        }
        
        // Insere a chave na posição correta
        array[j + 1] = chave;
    }
}

void insercao_binaria(int *array, int tamanho, long *comparacoes, long *trocas)
{
    for (int i = 1; i < tamanho; i++) {
        int chave = array[i];
        
        // Busca binária para encontrar posição de inserção
        int esquerda = 0;
        int direita = i - 1;
        int posicao = i;
        
        while (esquerda <= direita) {
            int meio = (esquerda + direita) / 2;
            
            if (comparar(array[meio], chave, comparacoes) > 0) {
                posicao = meio;
                direita = meio - 1;
            } else {
                esquerda = meio + 1;
            }
        }
        
        // Desloca elementos para abrir espaço
        for (int j = i; j > posicao; j--) {
            array[j] = array[j - 1];
            (*trocas)++;
        }
        
        // Insere a chave
        array[posicao] = chave;
    }
}

void insercao_ternaria(int *array, int tamanho, long *comparacoes, long *trocas)
{
    for (int i = 1; i < tamanho; i++) {
        int chave = array[i];
        
        // Busca ternária para encontrar posição de inserção
        int esquerda = 0;
        int direita = i - 1;
        int posicao = i;
        
        while (esquerda <= direita) {
            // Divide em três partes ao invés de duas
            int meio1 = esquerda + (direita - esquerda) / 3;
            int meio2 = esquerda + 2 * (direita - esquerda) / 3;
            
            int cmp1 = comparar(array[meio1], chave, comparacoes);
            int cmp2 = comparar(array[meio2], chave, comparacoes);
            
            if (cmp1 > 0) {
                direita = meio1 - 1;
                posicao = meio1;
            } else if (cmp2 > 0) {
                esquerda = meio1 + 1;
                direita = meio2 - 1;
                posicao = meio2;
            } else {
                esquerda = meio2 + 1;
            }
        }
        
        // Desloca elementos para abrir espaço
        for (int j = i; j > posicao; j--) {
            array[j] = array[j - 1];
            (*trocas)++;
        }
        
        // Insere a chave
        array[posicao] = chave;
    }
}

void selecao_direta(int *array, int tamanho, long *comparacoes, long *trocas)
{
    // Para cada posição, encontra o mínimo
    for (int i = 0; i < tamanho - 1; i++) {
        int indice_minimo = i;
        
        // Procura o elemento mínimo no restante do array
        for (int j = i + 1; j < tamanho; j++) {
            if (comparar(array[j], array[indice_minimo], comparacoes) < 0) {
                indice_minimo = j;
            }
        }
        
        // Coloca o mínimo na posição i
        if (indice_minimo != i) {
            trocar(&array[i], &array[indice_minimo], trocas);
        }
    }
}

void shell_sort(int *array, int tamanho, long *comparacoes, long *trocas)
{
    // Usa sequência de gaps: h = 3*h + 1
    // Começa com o maior h menor que tamanho/3
    int h = 1;
    while (h < tamanho / 3) {
        h = 3 * h + 1;  // Sequência: 1, 4, 13, 40, 121, ...
    }
    
    // Reduz gap até 1
    while (h >= 1) {
        // Para cada posição, insere com gap h (similar a inserção direta)
        for (int i = h; i < tamanho; i++) {
            int j = i;
            int chave = array[i];
            
            // Compara e troca com intervalos de h
            while (j >= h && comparar(array[j - h], chave, comparacoes) > 0) {
                array[j] = array[j - h];
                (*trocas)++;
                j -= h;
            }
            
            array[j] = chave;
        }
        
        // Reduz o gap (h = h / 3)
        h /= 3;
    }
}

/* ========== ALGORITMOS AVANÇADOS ========== */

/**
 * Função auxiliar para heap sort.
 * Restaura a propriedade de heap a partir de um índice.
 */
static void desce(int *array, int tamanho, int indice, long *comparacoes, long *trocas)
{
    int maior = indice;
    int esquerdo = 2 * indice + 1;
    int direito = 2 * indice + 2;
    
    // Encontra o maior entre pai e filhos
    if (esquerdo < tamanho && comparar(array[esquerdo], array[maior], comparacoes) > 0) {
        maior = esquerdo;
    }
    
    if (direito < tamanho && comparar(array[direito], array[maior], comparacoes) > 0) {
        maior = direito;
    }
    
    // Se filho é maior, troca e continua recursivamente
    if (maior != indice) {
        trocar(&array[indice], &array[maior], trocas);
        desce(array, tamanho, maior, comparacoes, trocas);
    }
}

void heap_sort(int *array, int tamanho, long *comparacoes, long *trocas)
{
    // Constrói heap máximo a partir do array
    // Começa do último nó pai: tamanho/2 - 1
    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        desce(array, tamanho, i, comparacoes, trocas);
    }
    
    // Remove elementos do heap um por um
    for (int i = tamanho - 1; i > 0; i--) {
        // Move raiz (máximo) para o final
        trocar(&array[0], &array[i], trocas);
        
        // Restaura propriedade de heap no array reduzido
        desce(array, i, 0, comparacoes, trocas);
    }
}

/**
 * Função auxiliar para quicksort com pivô no centro.
 * Particiona o array usando o elemento central como pivô.
 */
static int particionar_centro(int *array, int esquerda, int direita, 
                              long *comparacoes, long *trocas)
{
    int meio = esquerda + (direita - esquerda) / 2;
    int pivo = array[meio];
    
    // Move pivô para o final
    trocar(&array[meio], &array[direita], trocas);
    
    int i = esquerda;
    
    // Particiona: coloca menores à esquerda, maiores/iguais à direita
    for (int j = esquerda; j < direita; j++) {
        if (comparar(array[j], pivo, comparacoes) < 0) {
            trocar(&array[i], &array[j], trocas);
            i++;
        }
    }
    
    // Coloca pivô na posição final
    trocar(&array[i], &array[direita], trocas);
    return i;
}

/**
 * Função auxiliar recursiva para quicksort com pivô no centro.
 */
static void quicksort_centro_rec(int *array, int esquerda, int direita,
                                 long *comparacoes, long *trocas)
{
    if (esquerda < direita) {
        int pivo_pos = particionar_centro(array, esquerda, direita, comparacoes, trocas);
        
        quicksort_centro_rec(array, esquerda, pivo_pos - 1, comparacoes, trocas);
        quicksort_centro_rec(array, pivo_pos + 1, direita, comparacoes, trocas);
    }
}

void quicksort_centro(int *array, int tamanho, long *comparacoes, long *trocas)
{
    if (tamanho <= 1) return;
    quicksort_centro_rec(array, 0, tamanho - 1, comparacoes, trocas);
}

/**
 * Função auxiliar para mediana de 3.
 * Retorna o índice do elemento mediano entre a, b, c.
 */
static int mediana_tres(int *array, int a, int b, int c, long *comparacoes)
{
    if (comparar(array[a], array[b], comparacoes) <= 0) {
        if (comparar(array[b], array[c], comparacoes) <= 0) {
            return b;
        } else if (comparar(array[a], array[c], comparacoes) <= 0) {
            return c;
        } else {
            return a;
        }
    } else {
        if (comparar(array[a], array[c], comparacoes) <= 0) {
            return a;
        } else if (comparar(array[b], array[c], comparacoes) <= 0) {
            return c;
        } else {
            return b;
        }
    }
}

/**
 * Função auxiliar para quicksort com pivô pela mediana de 3.
 */
static int particionar_mediana(int *array, int esquerda, int direita,
                               long *comparacoes, long *trocas)
{
    int meio = esquerda + (direita - esquerda) / 2;
    int pivo_idx = mediana_tres(array, esquerda, meio, direita, comparacoes);
    int pivo = array[pivo_idx];
    
    // Move pivô para o final
    trocar(&array[pivo_idx], &array[direita], trocas);
    
    int i = esquerda;
    
    // Particiona
    for (int j = esquerda; j < direita; j++) {
        if (comparar(array[j], pivo, comparacoes) < 0) {
            trocar(&array[i], &array[j], trocas);
            i++;
        }
    }
    
    trocar(&array[i], &array[direita], trocas);
    return i;
}

/**
 * Função auxiliar recursiva para quicksort com mediana.
 */
static void quicksort_mediana_rec(int *array, int esquerda, int direita,
                                  long *comparacoes, long *trocas)
{
    if (esquerda < direita) {
        int pivo_pos = particionar_mediana(array, esquerda, direita, comparacoes, trocas);
        
        quicksort_mediana_rec(array, esquerda, pivo_pos - 1, comparacoes, trocas);
        quicksort_mediana_rec(array, pivo_pos + 1, direita, comparacoes, trocas);
    }
}

void quicksort_mediana(int *array, int tamanho, long *comparacoes, long *trocas)
{
    if (tamanho <= 1) return;
    quicksort_mediana_rec(array, 0, tamanho - 1, comparacoes, trocas);
}

/**
 * Função auxiliar para merge sort.
 * Mescla dois subarrays ordenados em um único array ordenado.
 */
static void mesclar(int *array, int esquerda, int meio, int direita,
                    long *comparacoes, long *trocas)
{
    int tamanho_esq = meio - esquerda + 1;
    int tamanho_dir = direita - meio;
    
    // Aloca arrays temporários
    int *arr_esq = (int *)malloc(tamanho_esq * sizeof(int));
    int *arr_dir = (int *)malloc(tamanho_dir * sizeof(int));
    
    // Copia dados para arrays temporários
    for (int i = 0; i < tamanho_esq; i++) {
        arr_esq[i] = array[esquerda + i];
    }
    for (int i = 0; i < tamanho_dir; i++) {
        arr_dir[i] = array[meio + 1 + i];
    }
    
    // Mescla os arrays temporários de volta
    int i = 0, j = 0, k = esquerda;
    
    while (i < tamanho_esq && j < tamanho_dir) {
        if (comparar(arr_esq[i], arr_dir[j], comparacoes) <= 0) {
            array[k++] = arr_esq[i++];
        } else {
            array[k++] = arr_dir[j++];
        }
        (*trocas)++;  // Conta cópia como troca
    }
    
    // Copia elementos restantes
    while (i < tamanho_esq) {
        array[k++] = arr_esq[i++];
        (*trocas)++;
    }
    
    while (j < tamanho_dir) {
        array[k++] = arr_dir[j++];
        (*trocas)++;
    }
    
    free(arr_esq);
    free(arr_dir);
}

/**
 * Função auxiliar recursiva para merge sort.
 */
static void merge_sort_rec(int *array, int esquerda, int direita,
                          long *comparacoes, long *trocas)
{
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        
        merge_sort_rec(array, esquerda, meio, comparacoes, trocas);
        merge_sort_rec(array, meio + 1, direita, comparacoes, trocas);
        mesclar(array, esquerda, meio, direita, comparacoes, trocas);
    }
}

void merge_sort(int *array, int tamanho, long *comparacoes, long *trocas)
{
    if (tamanho <= 1) return;
    merge_sort_rec(array, 0, tamanho - 1, comparacoes, trocas);
}

/* ========== ALGORITMOS NÃO-COMPARATIVOS ========== */

/**
 * Radix Sort - Ordena números inteiros processando cada dígito.
 * Usa counting sort como algoritmo de ordenação auxiliar para cada dígito.
 */
void radix_sort(int *array, int tamanho, long *comparacoes, long *trocas)
{
    if (tamanho <= 1) return;
    
    // Encontra o número máximo para determinar quantos dígitos processar
    int max_num = array[0];
    for (int i = 1; i < tamanho; i++) {
        if (array[i] > max_num) {
            max_num = array[i];
        }
    }
    
    // Array auxiliar para counting sort
    int *saida = (int *)malloc(tamanho * sizeof(int));
    
    // Processa cada dígito (unidade, dezena, centena, etc.)
    for (int exp = 1; max_num / exp > 0; exp *= 10) {
        // Counting sort para dígitos na posição exp
        int conta[10] = {0};
        
        // Conta ocorrências de cada dígito
        for (int i = 0; i < tamanho; i++) {
            int digito = (array[i] / exp) % 10;
            conta[digito]++;
            (*comparacoes)++;  // Conta como comparação
        }
        
        // Converte contagem para posições cumulativas
        for (int i = 1; i < 10; i++) {
            conta[i] += conta[i - 1];
        }
        
        // Coloca elementos no array de saída
        for (int i = tamanho - 1; i >= 0; i--) {
            int digito = (array[i] / exp) % 10;
            saida[conta[digito] - 1] = array[i];
            conta[digito]--;
            (*trocas)++;  // Conta cópia como troca
        }
        
        // Copia de volta para array original
        for (int i = 0; i < tamanho; i++) {
            array[i] = saida[i];
        }
    }
    
    free(saida);
}

/**
 * Bucket Sort - Distribui elementos em buckets e ordena cada um.
 * Assume números no intervalo [0, 9999] para este problema.
 */
void bucket_sort(int *array, int tamanho, long *comparacoes, long *trocas)
{
    if (tamanho <= 1) return;
    
    // Encontra máximo e mínimo
    int max_num = array[0];
    int min_num = array[0];
    
    for (int i = 1; i < tamanho; i++) {
        if (array[i] > max_num) {
            max_num = array[i];
        }
        if (array[i] < min_num) {
            min_num = array[i];
        }
    }
    
    // Número de buckets
    int num_buckets = (max_num - min_num) / 10 + 1;
    if (num_buckets < 10) num_buckets = 10;
    
    // Cria buckets
    int **buckets = (int **)malloc(num_buckets * sizeof(int *));
    int *tamanho_bucket = (int *)malloc(num_buckets * sizeof(int));
    
    for (int i = 0; i < num_buckets; i++) {
        buckets[i] = (int *)malloc(tamanho * sizeof(int));
        tamanho_bucket[i] = 0;
    }
    
    // Distribui elementos nos buckets
    for (int i = 0; i < tamanho; i++) {
        int indice_bucket = (array[i] - min_num) / 10;
        if (indice_bucket >= num_buckets) {
            indice_bucket = num_buckets - 1;
        }
        
        buckets[indice_bucket][tamanho_bucket[indice_bucket]++] = array[i];
        (*comparacoes)++;  // Conta distribuição como comparação
    }
    
    // Ordena cada bucket usando insertion sort e mescla
    int indice = 0;
    
    for (int i = 0; i < num_buckets; i++) {
        // Insertion sort em cada bucket
        for (int j = 1; j < tamanho_bucket[i]; j++) {
            int chave = buckets[i][j];
            int k = j - 1;
            
            while (k >= 0 && comparar(buckets[i][k], chave, comparacoes) > 0) {
                buckets[i][k + 1] = buckets[i][k];
                (*trocas)++;
                k--;
            }
            buckets[i][k + 1] = chave;
        }
        
        // Mescla bucket ordenado no array final
        for (int j = 0; j < tamanho_bucket[i]; j++) {
            array[indice++] = buckets[i][j];
        }
    }
    
    // Libera memória
    for (int i = 0; i < num_buckets; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(tamanho_bucket);
}
