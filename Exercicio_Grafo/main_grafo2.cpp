#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 5

// Estrutura do grafo
typedef struct Graph {
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Função para criar um grafo e inicializar a matriz de adjacência
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // Inicializando a matriz com 0 (sem conexão)
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Função para adicionar uma aresta ao grafo
void addEdge(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1; // Para grafos não direcionados
}

// Função para imprimir a matriz de adjacência
void printGraph(Graph* graph) {
    printf("Matriz de Adjacencia:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Programa principal
int main() {
    int vertices = MAX_VERTICES;
    Graph* graph = createGraph(vertices);

    // Adicionando algumas arestas
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printGraph(graph);

    free(graph);
    return 0;
}

