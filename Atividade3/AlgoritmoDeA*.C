//Atividade 3
//Algoritmo de A*
//Heurística

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define V 6  // Número de vértices no grafo
#define INF 1000000

typedef struct {
    int no;
    int g;  // Custo do caminho
    int f;  // g + h
} No;

int heuristica(int atual, int objetivo) {
    // Função heurística (exemplo: distância Euclidiana)
    int heuristicas[V] = {100, 67, 36, 56, 10, 8};  // Distâncias estimadas do exemplo
    return heuristicas[atual];
}

int menorF(No nos[], bool conjuntoFechado[], int tamanho) {
    int minimo = INF, indice_minimo = -1;
    for (int i = 0; i < tamanho; i++) {
        if (!conjuntoFechado[nos[i].no] && nos[i].f < minimo) {
            minimo = nos[i].f;
            indice_minimo = i;
        }
    }
    return indice_minimo;
}

void aEstrela(int grafo[V][V], int inicio, int objetivo) {
    bool conjuntoFechado[V] = {false};  // Lista de nós já avaliados
    bool conjuntoAberto[V] = {false};   // Lista de nós ainda a serem avaliados
    No nos[V];                          // Lista de nós para armazenar g e f

    for (int i = 0; i < V; i++) {
        nos[i].no = i;
        nos[i].g = INF;
        nos[i].f = INF;
    }

    nos[inicio].g = 0;
    nos[inicio].f = heuristica(inicio, objetivo);
    conjuntoAberto[inicio] = true;

    while (true) {
        int indiceAtual = menorF(nos, conjuntoFechado, V);
        if (indiceAtual == -1) {
            printf("Caminho não encontrado!\n");
            return;
        }

        No atual = nos[indiceAtual];
        if (atual.no == objetivo) {
            printf("Caminho encontrado com custo %d\n", atual.g);
            return;
        }

        conjuntoAberto[atual.no] = false;
        conjuntoFechado[atual.no] = true;

        for (int i = 0; i < V; i++) {
            if (grafo[atual.no][i] && !conjuntoFechado[i]) {
                int g_tentativo = atual.g + grafo[atual.no][i];
                if (!conjuntoAberto[i]) {
                    conjuntoAberto[i] = true;
                } else if (g_tentativo >= nos[i].g) {
                    continue;
                }

                nos[i].g = g_tentativo;
                nos[i].f = nos[i].g + heuristica(i, objetivo);
            }
        }
    }
}

int main() {
    // Representação do grafo como uma matriz de adjacência
    int grafo[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    aEstrela(grafo, 0, 5);  // Encontra o menor caminho do nó 0 ao nó 5

    return 0;
}
