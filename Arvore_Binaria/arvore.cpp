#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"
#include "product.h"

void insertNode(NodePtr *nodePtr, Product product){
    printf("Inserindo produto %s\n", product.name);
    if(*nodePtr == NULL){
        // Arvore vazia
        *nodePtr = (node*)malloc(sizeof(node));

        if(*nodePtr != NULL){
            (*nodePtr)->product = product;
            (*nodePtr)->leftPtr = NULL;
            (*nodePtr)->rightPtr = NULL;

            printf("Produto %s inserido com sucesso\n", product.name);
        } else {
            printf("Erro ao inserir o produto %s\n", product.name);
        }

    } else {
        // Arvore nao esta vazia

        if(product.ID < (*nodePtr)->product.ID) {
            insertNode( &((*nodePtr)->leftPtr), product);
        }
        else if(product.ID > (*nodePtr)->product.ID) {
            insertNode( &(*nodePtr)->rightPtr, product);
        }
        else {
            // Valor duplicado
            printf("Produto %s com ID[%d] ja existente\n", product.name, product.ID);
        }
    }
}

void inOrder(NodePtr nodePtr){
    if(nodePtr != NULL){
        inOrder(nodePtr->leftPtr);
        printf("(%2d) ", nodePtr->product.ID);
        inOrder(nodePtr->rightPtr);
    }
}


void preOrder(NodePtr nodePtr){
    if(nodePtr != NULL){
        printf("(%2d) ", nodePtr->product.ID);
        preOrder(nodePtr->leftPtr);
        preOrder(nodePtr->rightPtr);
    }
}


void posOrder(NodePtr nodePtr){
    if(nodePtr != NULL){
        posOrder(nodePtr->leftPtr);
        posOrder(nodePtr->rightPtr);
        printf("(%2d) ", nodePtr->product.ID);
    }
}

void searchAndPrintNode(NodePtr nodePtr, int ID) {
    if (nodePtr == NULL) {
        printf("Produto com ID[%d] nao encontrado\n", ID);
        return;
    }

    if (ID < nodePtr->product.ID) {
        searchAndPrintNode(nodePtr->leftPtr, ID);
    } else if (ID > nodePtr->product.ID) {
        searchAndPrintNode(nodePtr->rightPtr, ID);
    } else {
        printf("Produto encontrado!\n");
        printProduct(nodePtr->product);
    }
}

NodePtr searchNode(NodePtr nodePtr, int ID){

    if(nodePtr == NULL){
        printf("Produto com ID[%d] nao encontrado\n", ID);
        return NULL;
    }

    if(ID < nodePtr->product.ID){
        return searchNode(nodePtr->leftPtr, ID);
    } else if(ID > nodePtr->product.ID){
        return searchNode(nodePtr->rightPtr, ID);
    } else {
        return nodePtr;
    }
    
}

void searchNode(NodePtr nodePtr, int ID, NodePtr *foundNode, NodePtr *parentNode) {
    *foundNode = NULL;
    *parentNode = NULL;
    
    NodePtr current = nodePtr;
    NodePtr parent = NULL;

    while (current != NULL) {
        if (ID < current->product.ID) {
            parent = current;
            current = current->leftPtr;
        } else if (ID > current->product.ID) {
            parent = current;
            current = current->rightPtr;
        } else {
            *foundNode = current;
            *parentNode = parent;
            return;
        }
    }

    printf("Produto com ID[%d] nao encontrado\n", ID);
}

// Função auxiliar para encontrar o menor nó na subárvore direita
NodePtr findMin(NodePtr node) {
    while (node->leftPtr != NULL) {
        node = node->leftPtr;
    }
    return node;
}

// Função para remover um nó da árvore binária de busca
NodePtr removeNode(NodePtr nodePtr, int ID) {
    if (nodePtr == NULL) {
        printf("Produto com ID[%d] não encontrado\n", ID);
        return NULL;
    }

    if (ID < nodePtr->product.ID) {
        nodePtr->leftPtr = removeNode(nodePtr->leftPtr, ID);
    } else if (ID > nodePtr->product.ID) {
        nodePtr->rightPtr = removeNode(nodePtr->rightPtr, ID);
    } else {
        // Caso 1: Nó sem filhos
        if (nodePtr->leftPtr == NULL && nodePtr->rightPtr == NULL) {
            free(nodePtr);
            return NULL;
        }
        // Caso 2: Nó com apenas um filho
        else if (nodePtr->leftPtr == NULL) {
            NodePtr temp = nodePtr->rightPtr;
            free(nodePtr);
            return temp;
        } else if (nodePtr->rightPtr == NULL) {
            NodePtr temp = nodePtr->leftPtr;
            free(nodePtr);
            return temp;
        }
        // Caso 3: Nó com dois filhos
        else {
            NodePtr temp = findMin(nodePtr->rightPtr); // Encontra o menor da subárvore direita
            nodePtr->product = temp->product; // Copia os dados do sucessor
            nodePtr->rightPtr = removeNode(nodePtr->rightPtr, temp->product.ID); // Remove o sucessor
        }
    }
    return nodePtr;
}

void freeTree(NodePtr nodePtr) {
    if (nodePtr != NULL) {
        freeTree(nodePtr->leftPtr);
        freeTree(nodePtr->rightPtr);
        free(nodePtr);
    }
}
