#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "product.h"

void testesAutomatizados(NodePtr *rootPtr) {
    printf("\n=== INICIANDO TESTES AUTOMATIZADOS ===\n");

    // 1 INSERIR PRODUTOS AUTOMATICAMENTE
    Product produtos[] = { 
        {41, "Notebook", 3500.50, 10},
        {20, "Mouse", 120.75, 50},
        {65, "Teclado", 250.00, 30},
        {11, "Monitor", 899.99, 15},
        {29, "Cadeira Gamer", 1299.00, 5},
        {50, "Headset", 499.90, 20},
        {91, "Impressora", 750.00, 8},
        {1, "Pendrive", 45.00, 100},
        {15, "HD Externo", 350.00, 25},
        {27, "Webcam", 199.99, 18},
        {32, "Carregador", 89.90, 40},
        {45, "Microfone", 329.99, 12},
        {55, "Roteador", 599.90, 9},
        {72, "Tablet", 1899.00, 6},
        {99, "Smartphone", 3999.00, 14}
    };

    printf("\nInserindo produtos...\n");
    int produtosLen = (sizeof(produtos) / sizeof(Product));
    for (int i = 0; i < produtosLen; i++) {
        insertNode(rootPtr, produtos[i]);
    }

    printf("\nListando produtos (In-Order)...\n");
    inOrder(*rootPtr);
    printf("\n");

    // 2 BUSCAR PRODUTOS EXISTENTES
    printf("\nBuscando produtos existentes...\n");
    int idsParaBuscar[] = {41, 11, 91};
    for (int i = 0; i < 3; i++) {
        printf("\nBuscando ID %d...\n", idsParaBuscar[i]);
        searchAndPrintNode(*rootPtr, idsParaBuscar[i]);
    }

    // 3 BUSCAR PRODUTO INEXISTENTE
    printf("\nBuscando um produto inexistente (ID 99)...\n");
    searchAndPrintNode(*rootPtr, 99);

    // 4 ATUALIZAR UM PRODUTO
    int idParaAtualizar = 65;
    NodePtr searchedNode = searchNode(*rootPtr, idParaAtualizar);
    if (searchedNode != NULL) {
        printf("\nAtualizando produto com ID %d...\n", idParaAtualizar);
        searchedNode->product.price = 150.00;
        searchedNode->product.stock = 100;
        printf("Produto atualizado! Novo preco: %.2f, Novo estoque: %d\n", searchedNode->product.price, searchedNode->product.stock);
    }

    // 5 REMOVER UM PRODUTO
    int idParaRemover = 29;
    printf("\nRemovendo produto com ID %d...\n", idParaRemover);
    *rootPtr = removeNode(*rootPtr, idParaRemover);

    printf("\nListando produtos apos remocao (In-Order)...\n");
    inOrder(*rootPtr);
    printf("\n");

    printf("\nTestes automatizados finalizados!\n");
}

int main() {
    NodePtr rootPtr = NULL;

    // Rodando os testes automatizados antes do menu interativo
    testesAutomatizados(&rootPtr);
    system("pause");

    // MENU INTERATIVO (opcional, para testar manualmente)
    bool menu = true;
    while (menu) {
        system("cls");

        printf("\n[1] Inserir   produto\n");
        printf("[2] Buscar    produto\n");
        printf("[3] Remover   produto\n");
        printf("[4] Listar    produtos\n");
        printf("[5] Atualizar produto\n");
        printf("[6] Sair\n");

        int opcao;
        scanf("%d", &opcao);

        Product *product;
        NodePtr searchedNode;
        int ID;

        switch (opcao) {
            case 1:
                printf("\nInserir produto\n");
                product = (Product *)malloc(sizeof(Product));
                if (product != NULL) {
                    printf("Digite o ID do produto: ");
                    scanf("%d", &product->ID);
                    getchar();

                    printf("Digite o nome do produto: ");
                    fgets(product->name, 100, stdin);
                    product->name[strcspn(product->name, "\n")] = '\0';  // Remover quebra de linha

                    printf("Digite o preco do produto: ");
                    scanf("%f", &product->price);

                    printf("Digite o estoque do produto: ");
                    scanf("%d", &product->stock);

                    insertNode(&rootPtr, *product);
                    free(product);
                } else {
                    printf("Erro ao alocar memória para o produto\n");
                }
                break;

            case 2:
                printf("\nBuscar produto\n");
                printf("Digite o ID do produto: ");
                scanf("%d", &ID);
                searchAndPrintNode(rootPtr, ID);
                break;

            case 3:
                printf("\nRemover produto\n");
                printf("Digite o ID do produto a ser removido: ");
                scanf("%d", &ID);
                rootPtr = removeNode(rootPtr, ID);
                printf("Produto removido com sucesso!\n");
                break;

            case 4:
                printf("\nListar produtos (In-Order)...\n");
                inOrder(rootPtr);
                printf("\n");
                break;

            case 5:
                printf("\nAtualizar produto\n");
                printf("Digite o ID do produto: ");
                scanf("%d", &ID);
                searchedNode = searchNode(rootPtr, ID);
                if (searchedNode != NULL) {
                    printf("Produto encontrado: ID=%d, Preço=%.2f, Estoque=%d\n", 
                           searchedNode->product.ID, searchedNode->product.price, searchedNode->product.stock);

                    printf("Digite o novo preço: ");
                    scanf("%f", &searchedNode->product.price);

                    printf("Digite o novo estoque: ");
                    scanf("%d", &searchedNode->product.stock);

                    printf("Produto atualizado com sucesso!\n");
                } else {
                    printf("Produto não encontrado.\n");
                }
                break;

            case 6:
                printf("\nSaindo...\n");
                menu = false;
                freeTree(rootPtr);
                break;

            default:
                printf("\nOpcaoo invalida\n");
                break;
        }
    }

    return 0;
}
