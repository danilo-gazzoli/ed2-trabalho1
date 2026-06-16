/*
 * ============================================================================
 * timer.c
 * ============================================================================
 * Implementação do módulo de cronometragem.
 * ============================================================================
 */

#include "timer.h"

clock_t iniciar_cronometro(void)
{
    return clock();
}

double obter_tempo_decorrido(clock_t tempo_inicio)
{
    clock_t tempo_final = clock();
    
    // Converte para milissegundos: (tempo / CLOCKS_PER_SEC) * 1000
    double tempo_ms = ((double)(tempo_final - tempo_inicio) / CLOCKS_PER_SEC) * 1000.0;
    
    return tempo_ms;
}
