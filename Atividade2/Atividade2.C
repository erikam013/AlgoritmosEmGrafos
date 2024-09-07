//Atividade 2
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX], transposta[MAX][MAX], visitado[MAX], topo[MAX], descoberta[MAX], finalizacao[MAX], tempo;

void inicializar(int n) {
    for (int i = 0; i < n; i++) {
        visitado[i] = 0;
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
            transposta[i][j] = 0;
        }
    }
    tempo = 0;
}

void adicionarAresta(int u, int v) {
    adj[u][v] = 1;
}

void DFS(int v, int n) {
    visitado[v] = 1;
    descoberta[v] = ++tempo;
    printf("Visitando nó %d (descoberta = %d)\n", v, descoberta[v]);

    for (int i = 0; i < n; i++) {
        if (adj[v][i] == 1 && !visitado[i]) {
            DFS(i, n);
        }
    }
    finalizacao[v] = ++tempo;
    printf("Finalizando nó %d (finalização = %d)\n", v, finalizacao[v]);
    topo[--tempo] = v;
}

void ordenacaoTopologica(int n) {
    for (int i = 0; i < n; i++) {
        visitado[i] = 0;
    }
    tempo = n;
    printf("Ordenação Topológica:\n");
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            DFS(i, n);
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", topo[i]);
    }
    printf("\n");
}

void transporGrafo(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transposta[i][j] = adj[j][i];
        }
    }
}

void DFS_transposta(int v, int n) {
    visitado[v] = 1;
    descoberta[v] = ++tempo;
    printf("Visitando nó %d no grafo transposto (descoberta = %d)\n", v, descoberta[v]);

    for (int i = 0; i < n; i++) {
        if (transposta[v][i] == 1 && !visitado[i]) {
            DFS_transposta(i, n);
        }
    }
    finalizacao[v] = ++tempo;
    printf("Finalizando nó %d no grafo transposto (finalização = %d)\n", v, finalizacao[v]);
}

void componentesFortementeConectados(int n) {
    // Passo 1: Executar DFS no grafo original
    ordenacaoTopologica(n);

    // Passo 2: Transpor o grafo
    transporGrafo(n);

    // Passo 3: Executar DFS no grafo transposto na ordem decrescente de finalização
    for (int i = 0; i < n; i++) {
        visitado[i] = 0;
    }

    printf("\nComponentes Fortemente Conectados:\n");
    tempo = 0;
    for (int i = 0; i < n; i++) {
        if (!visitado[topo[i]]) {
            DFS_transposta(topo[i], n);
            printf("\n");
        }
    }
}

int main() {
    int n, arestas, u, v, inicio;

    printf("Número de nós: ");
    scanf("%d", &n);

    inicializar(n);

    printf("Número de arestas: ");
    scanf("%d", &arestas);

    for (int i = 0; i < arestas; i++) {
        printf("Digite as arestas (u v): ");
        scanf("%d %d", &u, &v);
        adicionarAresta(u, v);
    }

    printf("\nEscolha um nó para iniciar a ordenação topológica: ");
    scanf("%d", &inicio);

    printf("\nExecutando Ordenação Topológica:\n");
    DFS(inicio, n);

    printf("\nExecutando Componentes Fortemente Conectados:\n");
    componentesFortementeConectados(n);

    return 0;
}
