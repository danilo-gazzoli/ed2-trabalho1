#!/bin/bash

# ============================================================================
# escolher_teste.sh
# ============================================================================
# Menu para escolher qual input e qual algoritmo executar.
#
# Uso interativo:
#   bash escolher_teste.sh
#
# Uso direto:
#   bash escolher_teste.sh <numero_do_input> <id_algoritmo>
#
# Exemplo:
#   bash escolher_teste.sh 1 9
# ============================================================================

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

EXECUTAVEL="./main"

definir_executavel() {
    if [ -x "./main" ]; then
        EXECUTAVEL="./main"
    elif [ -x "./main.exe" ]; then
        EXECUTAVEL="./main.exe"
    else
        EXECUTAVEL="./main"
    fi
}

compilar_se_necessario() {
    definir_executavel

    precisa_compilar=0

    if [ ! -x "$EXECUTAVEL" ]; then
        precisa_compilar=1
    fi

    if [ "main.c" -nt "$EXECUTAVEL" ] 2>/dev/null; then
        precisa_compilar=1
    fi

    if [ "sorts.c" -nt "$EXECUTAVEL" ] 2>/dev/null; then
        precisa_compilar=1
    fi

    if [ "utils.c" -nt "$EXECUTAVEL" ] 2>/dev/null; then
        precisa_compilar=1
    fi

    if [ "timer.c" -nt "$EXECUTAVEL" ] 2>/dev/null; then
        precisa_compilar=1
    fi

    if [ "$precisa_compilar" -eq 1 ]; then
        echo "Compilando projeto..."
        gcc -Wall -Wextra -O3 -std=c99 main.c sorts.c utils.c timer.c -lm -o main

        if [ $? -ne 0 ]; then
            echo "Erro: a compilação falhou."
            exit 1
        fi

        definir_executavel

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

obter_nome_algoritmo() {
    id_procurado="$1"

    for item in "${ALGORITMOS[@]}"; do
        id="${item%%|*}"
        nome="${item#*|}"

        if [ "$id" = "$id_procurado" ]; then
            echo "$nome"
            return 0
        fi
    done

    echo "Algoritmo desconhecido"
    return 1
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

if ! validar_numero "$escolha_input"; then
    echo "Erro: input inválido. Digite apenas números."
    exit 1
fi

if [ "$escolha_input" -lt 1 ] || [ "$escolha_input" -gt "${#ARQUIVOS[@]}" ]; then
    echo "Erro: input inválido. Escolha um número de 1 a ${#ARQUIVOS[@]}."
    exit 1
fi

if ! validar_numero "$escolha_algoritmo"; then
    echo "Erro: algoritmo inválido. Digite apenas números."
    exit 1
fi

if [ "$escolha_algoritmo" -lt 1 ] || [ "$escolha_algoritmo" -gt 13 ]; then
    echo "Erro: algoritmo inválido. Escolha um ID de 1 a 13."
    exit 1
fi

arquivo_escolhido="${ARQUIVOS[$((escolha_input - 1))]}"
algoritmo_escolhido="$(obter_nome_algoritmo "$escolha_algoritmo")"

if [ ! -f "$arquivo_escolhido" ]; then
    echo "Erro: o arquivo escolhido não foi encontrado:"
    echo "$arquivo_escolhido"
    echo
    echo "Verifique se ele está dentro da pasta Instâncias/Instâncias/."
    exit 1
fi

if ! command -v timeout >/dev/null 2>&1; then
    echo "Erro: o comando 'timeout' não foi encontrado."
    echo
    echo "Para usar o limite de 24 horas, execute este script no Git Bash, WSL ou Linux."
    exit 1
fi

echo "================================================================================"
echo "EXECUTANDO TESTE ESCOLHIDO"
echo "Input:      $arquivo_escolhido"
echo "Algoritmo:  $escolha_algoritmo - $algoritmo_escolhido"
echo "Limite:     24 horas"
echo "================================================================================"
echo

echo "Iniciando execução com limite máximo de 24 horas..."
echo

timeout 24h "$EXECUTAVEL" "$arquivo_escolhido" "$escolha_algoritmo"

STATUS=$?

if [ "$STATUS" -eq 124 ]; then
    echo
    echo "================================================================================"
    echo "TEMPO LIMITE ESGOTADO"
    echo "================================================================================"
    echo "O algoritmo ultrapassou o limite máximo de 24 horas."
    echo "Input utilizado:      $arquivo_escolhido"
    echo "Algoritmo utilizado:  $escolha_algoritmo - $algoritmo_escolhido"
    echo "Resultado:            TIMEOUT"
    echo "================================================================================"

    echo "$arquivo_escolhido;$escolha_algoritmo;$algoritmo_escolhido;TIMEOUT_24H" >> timeout_resultados.txt

    exit 124
fi

if [ "$STATUS" -ne 0 ]; then
    echo
    echo "================================================================================"
    echo "ERRO NA EXECUÇÃO"
    echo "================================================================================"
    echo "Ocorreu uma falha durante a execução do algoritmo."
    echo "Input utilizado:      $arquivo_escolhido"
    echo "Algoritmo utilizado:  $escolha_algoritmo - $algoritmo_escolhido"
    echo "Código de erro:       $STATUS"
    echo "================================================================================"

    exit "$STATUS"
fi

echo
echo "================================================================================"
echo "EXECUÇÃO FINALIZADA COM SUCESSO"
echo "================================================================================"
echo "Input utilizado:      $arquivo_escolhido"
echo "Algoritmo utilizado:  $escolha_algoritmo - $algoritmo_escolhido"
echo "Arquivo gerado:       saida.txt"
echo "================================================================================"