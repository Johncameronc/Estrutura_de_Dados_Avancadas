#ifndef ARVORE_H
#define ARVORE_H

#include "product.h"

typedef struct node {
    Product product;
    struct node *leftPtr;
    struct node *rightPtr;
} Node;

typedef Node *NodePtr;

void insertNode(NodePtr *nodePtr, Product product);
void inOrder(NodePtr nodePtr);
void preOrder(NodePtr nodePtr);
void posOrder(NodePtr nodePtr);
void searchAndPrintNode(NodePtr nodePtr, int ID);
NodePtr searchNode(NodePtr nodePtr, int ID);

NodePtr findMin(NodePtr node);
NodePtr removeNode(NodePtr nodePtr, int ID);

void freeTree(NodePtr nodePtr);

#endif
