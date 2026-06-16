#!/bin/bash

# Menu para escolher qual input e qual algoritmo executar.
# Uso interativo:
#   bash escolher_teste.sh
#
# Uso direto:
#   bash escolher_teste.sh <numero_do_input> <id_algoritmo>
# Exemplo:
#   bash escolher_teste.sh 1 9

set -u

cd "$(dirname "$0")"

ARQUIVOS=(
    "Instâncias/Instâncias/10000_aleatorio.txt"
    "Instâncias/Instâncias/10000_ordenado_crescente.txt"
    "Instâncias/Instâncias/10000_ordenado_decrescente.txt"
    "Instâncias/Instâncias/1000000_aleatorio.txt"
    "Instâncias/Instâncias/1000000_ordenado_crescente.txt"
    "Instâncias/Instâncias/1000000_ordenado_decrescente.txt"
)

ALGORITMOS=(
    "1|Bubble Sort"
    "2|Bubble Sort Otimizado"
    "3|Insertion Sort (Direto)"
    "4|Insertion Sort (Binário)"
    "5|Insertion Sort (Ternário)"
    "6|Selection Sort"
    "7|Shell Sort"
    "8|Heap Sort"
    "9|QuickSort (Centro)"
    "10|QuickSort (Mediana de 3)"
    "11|Merge Sort"
    "12|Radix Sort"
    "13|Bucket Sort"
)

compilar_se_necessario() {
    if [ ! -x "./main" ] || [ "main.c" -nt "main" ] || [ "sorts.c" -nt "main" ] || [ "utils.c" -nt "main" ] || [ "timer.c" -nt "main" ]; then
        echo "Compilando projeto..."
        gcc -Wall -Wextra -O3 -std=c99 main.c sorts.c utils.c timer.c -lm -o main
        if [ $? -ne 0 ]; then
            echo "Erro: a compilação falhou."
            exit 1
        fi
        echo "✓ Compilação concluída."
        echo
    fi
}

mostrar_inputs() {
    echo "Escolha o input:"
    for i in "${!ARQUIVOS[@]}"; do
        numero=$((i + 1))
        arquivo="${ARQUIVOS[$i]}"
        if [ -f "$arquivo" ]; then
            echo "  $numero - $arquivo"
        else
            echo "  $numero - $arquivo  [NÃO ENCONTRADO]"
        fi
    done
    echo
}

mostrar_algoritmos() {
    echo "Escolha o algoritmo:"
    for item in "${ALGORITMOS[@]}"; do
        id="${item%%|*}"
        nome="${item#*|}"
        printf "  %2d - %s\n" "$id" "$nome"
    done
    echo
}

validar_numero() {
    [[ "$1" =~ ^[0-9]+$ ]]
}

compilar_se_necessario

if [ $# -eq 2 ]; then
    escolha_input="$1"
    escolha_algoritmo="$2"
elif [ $# -eq 0 ]; then
    mostrar_inputs
    read -r -p "Digite o número do input: " escolha_input
    echo
    mostrar_algoritmos
    read -r -p "Digite o ID do algoritmo: " escolha_algoritmo
else
    echo "Uso: bash escolher_teste.sh"
    echo "ou:  bash escolher_teste.sh <numero_do_input> <id_algoritmo>"
    echo "Exemplo: bash escolher_teste.sh 1 9"
    exit 1
fi

if ! validar_numero "$escolha_input" || [ "$escolha_input" -lt 1 ] || [ "$escolha_input" -gt "${#ARQUIVOS[@]}" ]; then
    echo "Erro: input inválido. Escolha um número de 1 a ${#ARQUIVOS[@]}."
    exit 1
fi

if ! validar_numero "$escolha_algoritmo" || [ "$escolha_algoritmo" -lt 1 ] || [ "$escolha_algoritmo" -gt 13 ]; then
    echo "Erro: algoritmo inválido. Escolha um ID de 1 a 13."
    exit 1
fi

arquivo_escolhido="${ARQUIVOS[$((escolha_input - 1))]}"

if [ ! -f "$arquivo_escolhido" ]; then
    echo "Erro: o arquivo escolhido não foi encontrado:"
    echo "$arquivo_escolhido"
    echo
    echo "Verifique se ele está dentro da pasta Instâncias/Instâncias/."
    exit 1
fi

echo "================================================================================"
echo "EXECUTANDO TESTE ESCOLHIDO"
echo "Input:      $arquivo_escolhido"
echo "Algoritmo:  $escolha_algoritmo"
echo "================================================================================"
echo

./main "$arquivo_escolhido" "$escolha_algoritmo"