/*
 * ============================================================================
 * timer.h
 * ============================================================================
 * Módulo para medição de tempo de execução dos algoritmos de ordenação.
 * Utiliza funções do sistema para medir o tempo com precisão.
 * ============================================================================
 */

#ifndef TIMER_H
#define TIMER_H

#include <time.h>

/**
 * Inicia a contagem de tempo.
 * Retorna o tempo atual do sistema em milissegundos.
 */
clock_t iniciar_cronometro(void);

/**
 * Calcula o tempo decorrido entre o início e agora.
 * 
 * @param tempo_inicio: Tempo retornado por iniciar_cronometro()
 * @return Tempo decorrido em milissegundos (double)
 */
double obter_tempo_decorrido(clock_t tempo_inicio);

#endif
