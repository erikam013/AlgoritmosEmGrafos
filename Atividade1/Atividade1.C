//Atividade 1
#include <stdio.h>
#include <stdlib.h>

#define MAX_NOS 100

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* proxima;
} Aresta;

typedef struct Grafo {
    int numNos;
    Aresta* listaAdj[MAX_NOS];
    int ehDirecional;
    int ehPonderado;
} Grafo;

Grafo* criarGrafo(int numNos, int ehDirecional, int ehPonderado) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numNos = numNos;
    grafo->ehDirecional = ehDirecional;
    grafo->ehPonderado = ehPonderado;

    for (int i = 0; i < numNos; i++) {
        grafo->listaAdj[i] = NULL;
    }
    
    return grafo;
}

Aresta* criarAresta(int destino, int peso) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proxima = NULL;
    return novaAresta;
}

void adicionarAresta(Grafo* grafo, int origem, int destino, int peso) {
    Aresta* novaAresta = criarAresta(destino, peso);
    novaAresta->proxima = grafo->listaAdj[origem];
    grafo->listaAdj[origem] = novaAresta;

    if (!grafo->ehDirecional) {
        novaAresta = criarAresta(origem, peso);
        novaAresta->proxima = grafo->listaAdj[destino];
        grafo->listaAdj[destino] = novaAresta;
    }
}

void imprimirGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numNos; i++) {
        printf("%c ", 'A' + i);
        Aresta* temp = grafo->listaAdj[i];
        while (temp) {
            if (grafo->ehPonderado) {
                printf("(%c: %d) ", 'A' + temp->destino, temp->peso);
            } else {
                printf("(-> %c) ", 'A' + temp->destino);
            }
            temp = temp->proxima;
        }
        printf("\n");
    }
}

int main() {
    int numNos, origem, destino, peso, tipo;
    
    printf("Escolha o tipo de grafo:\n");
    printf("1 - Grafo direcional não ponderado\n");
    printf("2 - Grafo não direcional ponderado\n");
    scanf("%d", &tipo);

    printf("Digite o número de nós do grafo: ");
    scanf("%d", &numNos);

    Grafo* grafo = criarGrafo(numNos, tipo == 1, tipo == 2);

    while (1) {
        printf("Digite a origem e o destino da aresta (0 0 para sair): ");
        scanf("%d %d", &origem, &destino);

        if (origem == 0 && destino == 0) {
            break;
        }

        if (tipo == 2) {  // Grafo ponderado
            printf("Digite o peso da aresta: ");
            scanf("%d", &peso);
        } else {
            peso = 0;
        }

        adicionarAresta(grafo, origem - 1, destino - 1, peso);
    }

    printf("Grafo montado:\n");
    imprimirGrafo(grafo);

    return 0;
}
