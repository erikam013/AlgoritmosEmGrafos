//Atividade 3
//Algoritmo de Dijkstra
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6  // Número de vértices no grafo

// Função para encontrar o vértice com a menor distância
int menorDistancia(int dist[], bool conjuntoSPT[]) {
    int min = INT_MAX, indice_minimo;

    for (int v = 0; v < V; v++)
        if (conjuntoSPT[v] == false && dist[v] <= min)
            min = dist[v], indice_minimo = v;

    return indice_minimo;
}

// Função para imprimir a solução
void imprimirSolucao(int dist[]) {
    printf("Vértice \t Distância da Fonte\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Função para implementar o algoritmo de Dijkstra
void dijkstra(int grafo[V][V], int origem) {
    int dist[V];     // O array dist contém o menor caminho da origem para cada vértice
    bool conjuntoSPT[V];  // conjuntoSPT[i] é verdadeiro se o vértice i está incluído no menor caminho

    // Inicializa todas as distâncias como INFINITO e conjuntoSPT[] como falso
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, conjuntoSPT[i] = false;

    // Distância do vértice origem para ele mesmo é sempre 0
    dist[origem] = 0;

    // Encontra o caminho mais curto para todos os vértices
    for (int count = 0; count < V - 1; count++) {
        int u = menorDistancia(dist, conjuntoSPT);

        // Marca o vértice como processado
        conjuntoSPT[u] = true;

        // Atualiza o valor da distância dos vértices adjacentes do vértice escolhido
        for (int v = 0; v < V; v++)
            if (!conjuntoSPT[v] && grafo[u][v] && dist[u] != INT_MAX
                && dist[u] + grafo[u][v] < dist[v])
                dist[v] = dist[u] + grafo[u][v];
    }

    // Imprime o array de distâncias
    imprimirSolucao(dist);
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

    dijkstra(grafo, 0);  // Encontra o menor caminho a partir do vértice 0

    return 0;
}
