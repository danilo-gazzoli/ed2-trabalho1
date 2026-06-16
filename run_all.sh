#!/bin/bash

# Script para executar todos os 13 algoritmos com todos os 6 arquivos (78 testes)

ARQUIVOS=(
    "Instâncias/Instâncias/10000_aleatorio.txt"
    "Instâncias/Instâncias/10000_ordenado_crescente.txt"
    "Instâncias/Instâncias/10000_ordenado_decrescente.txt"
    "Instâncias/Instâncias/1000000_aleatorio.txt"
    "Instâncias/Instâncias/1000000_ordenado_crescente.txt"
    "Instâncias/Instâncias/1000000_ordenado_decrescente.txt"
)

ALGORITMOS=( {1..13} )

echo "================================================================================"
echo "EXECUTANDO TODOS OS TESTES (13 algoritmos × 6 arquivos = 78 testes)"
echo "================================================================================"
echo

printf "%-30s %-30s %15s %12s %10s\n" "ARQUIVO" "ALGORITMO" "COMPARAÇÕES" "TROCAS" "TEMPO"
printf "%-30s %-30s %15s %12s %10s\n" "--------" "---------" "------------" "------" "-----"

testes_ok=0
total_testes=$(( ${#ARQUIVOS[@]} * ${#ALGORITMOS[@]} ))

for arquivo in "${ARQUIVOS[@]}"; do
    for algo_id in "${ALGORITMOS[@]}"; do
        if ./main "$arquivo" "$algo_id" > /tmp/test_output.txt 2>&1; then
            # Extrai as 3 últimas linhas do resultado
            comp=$(grep "^Comparações" /tmp/test_output.txt | awk '{print $NF}')
            trocas=$(grep "^Trocas" /tmp/test_output.txt | awk '{print $NF}')
            tempo=$(grep "^Tempo (ms)" /tmp/test_output.txt | awk '{print $NF}')
            
            printf "%-30s %3d %-26s %15s %12s %10s\n" "$(basename $arquivo)" "$algo_id" "" "$comp" "$trocas" "$tempo"
            ((testes_ok++))
        else
            printf "%-30s %3d %-26s ERROR\n" "$(basename $arquivo)" "$algo_id" ""
        fi
    done
done

echo
echo "================================================================================"
echo "RESUMO: $testes_ok/$total_testes testes concluídos com sucesso"
echo "================================================================================"
echo
