#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

void clearScreen() {
    // Limpa a tela
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// estrutura para um no na lista de adjacencia
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// estrutura para o grafo
typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX_VERTICES];
} Graph;

int getIndex(Graph* graph, int vertex) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjLists[i]->vertex == vertex)
            return i;
    }
    return -1;
}

// funcao para criar novo no
Node* createNode(int vertex) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    
    newNode->vertex = vertex;
    newNode->next = NULL;
    
    return newNode;
}

Node* getNode(Graph* graph, int vertex) {
    // verificar se o vertice existe
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjLists[i]->vertex == vertex) {
            return graph->adjLists[i];
        }
    }

    return NULL;
}

// funcao para criar grafo
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) { 
        graph->adjLists[i] = NULL;
    }

    return graph;
}

Graph* addVertex(Graph* graph, int vertex) {
    // verificar se o vertice ja existe
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjLists[i]->vertex == vertex) {
            printf("parada %d ja existe!\n", vertex);
            return graph;
        }
    }

    // adicionar novo vertice ao grafo
    if (graph->numVertices < MAX_VERTICES) {
        graph->adjLists[graph->numVertices] = NULL;

        graph->adjLists[graph->numVertices] = createNode(vertex);
        graph->adjLists[graph->numVertices]->vertex = vertex;

        graph->numVertices++;
        printf("parada %d adicionada com sucesso!\n", graph->adjLists[graph->numVertices - 1]->vertex);
    } else {
        printf("limite de vertices atingido!\n");
    }
    return graph;
}

void addEdge(Graph* graph, int vSrc, int vDest) {
    int iSrc = getIndex(graph, vSrc);
    int iDest = getIndex(graph, vDest);
    if (iSrc < 0 || iDest < 0) return;

    // src -> dest
    Node* nodeD = createNode(vDest);
    nodeD->next = graph->adjLists[iSrc];
    graph->adjLists[iSrc] = nodeD;

    // dest -> src
    Node* nodeS = createNode(vSrc);
    nodeS->next = graph->adjLists[iDest];
    graph->adjLists[iDest] = nodeS;
}

// imprimir grafo
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        printf("vertice %d: ", graph->adjLists[i]->vertex);

        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

int main(){

    Graph* graph = createGraph(0);
    
    int opcao = -1, vertice;

    Node* src;
    Node* dest;
    Node* newNode;

    do {

        clearScreen();
        printf("=== sistema de rotas urbanas ===\n");
        printf("1. adicionar parada\n");
        printf("2. adicionar rota entre paradas\n");
        printf("3. mostrar mapa de rotas\n"); // lista de adjacencia
        printf("4. buscar rota entre duas paradas\n"); // busca em largura
        printf("5. listar paradas acessiveis\n"); // busca em profundidade
        printf("0. sair\n");
        printf("escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                // adicionar parada
                printf("=== adicionar parada ===\n");
                printf("digite o numero da parada: ");
                scanf("%d", &vertice);

                graph = addVertex(graph, vertice);
                
                system("pause");
                break;

            case 2:
                int vSrc, vDest;

                // adicionar rota entre paradas
                printf("=== adicionar rota entre paradas ===\n");
                printf("digite o numero da parada de origem: ");
                scanf("%d", &vSrc);
                src = getNode(graph, vertice);

                printf("digite o numero da parada de destino: ");
                scanf("%d", &vDest);
                dest = getNode(graph, vertice);

                if (src != NULL && dest != NULL) {
                    addEdge(graph, vSrc, vDest);
                    printf("rota entre %d e %d adicionada com sucesso!\n", src->vertex, dest->vertex);
                } else {
                    printf("uma ou mais paradas nao existem!\n");
                }
                
                break;

            case 3:
                // mostrar mapa de rotas
                printf("=== mapa de rotas ===\n");
                printGraph(graph);

                system("pause");
                break;

            case 4:
                break;

            case 5:
                break;

            case 0:
                // sair
                printf("saindo...\n");
                break;

            default:
                printf("opcao invalida!\n");
                break;

        }

    } while(opcao != 0);

}