#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int id = 0;

int getId() {
    return id++;
}

int altura_NO(struct treeNode *no) {
    if (no == NULL)
        return -1;
    return no->altura;
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

treeNode *novoNO(int Id, char nome[], char email[]) {
    struct treeNode *no = (struct treeNode *)malloc(sizeof(struct treeNode));

    no->Id = Id;
    strcpy(no->nome, nome);
    strcpy(no->email, email);
    
    no->altura = 0;
    no->esq = NULL;
    no->dir = NULL;

    return no;
}

struct treeNode *rotacaoRR(struct treeNode *raiz) {
    struct treeNode *no = raiz->dir;

    raiz->dir = no->esq;
    no->esq = raiz;
    raiz->altura = maior(altura_NO(raiz->esq), altura_NO(raiz->dir)) + 1;
    no->altura = maior(altura_NO(no->esq), altura_NO(no->dir)) + 1;

    return no;
}

struct treeNode *rotacaoLL(struct treeNode *raiz) {
    struct treeNode *no = raiz->esq;

    raiz->esq = no->dir;
    no->dir = raiz;
    raiz->altura = maior(altura_NO(raiz->esq), altura_NO(raiz->dir)) + 1;
    no->altura = maior(altura_NO(no->esq), altura_NO(no->dir)) + 1;

    return no;
}

struct treeNode *rotacaoLR(struct treeNode *raiz) {
    raiz->esq = rotacaoRR(raiz->esq);
    return rotacaoLL(raiz);
}

struct treeNode *rotacaoRL(struct treeNode *raiz) {
    raiz->dir = rotacaoLL(raiz->dir);
    return rotacaoRR(raiz);
}

int fatorBalanceamento(struct treeNode *raiz) {
    if (raiz == NULL)
        return 0;
    return altura_NO(raiz->esq) - altura_NO(raiz->dir);
}

struct treeNode *inserir(struct treeNode *raiz, int Id, char nome[], char email[]) {    
    if (raiz == NULL)
        return novoNO(Id, nome, email);

    int comparacao = strcmp(nome, raiz->nome);
    
    if (comparacao < 0)
        raiz->esq = inserir(raiz->esq, Id, nome, email);
    else if (comparacao > 0)
        raiz->dir = inserir(raiz->dir, Id, nome, email);
    else
        return raiz; // nome duplicado não permitido

    raiz->altura = maior(altura_NO(raiz->esq), altura_NO(raiz->dir)) + 1;

    int fb = fatorBalanceamento(raiz);

    // casos de desbalanceamento
    if (fb > 1 && strcmp(nome, raiz->esq->nome) < 0)
        return rotacaoLL(raiz);

    if (fb < -1 && strcmp(nome, raiz->dir->nome) > 0)
        return rotacaoRR(raiz);

    if (fb > 1 && strcmp(nome, raiz->esq->nome) > 0)
        return rotacaoLR(raiz);

    if (fb < -1 && strcmp(nome, raiz->dir->nome) < 0)
        return rotacaoRL(raiz);

    return raiz;
}

struct treeNode *menorValor(struct treeNode *no) {
    struct treeNode *atual = no;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

struct treeNode *remover(struct treeNode *raiz, char nome[]) {
    if (raiz == NULL)
        return raiz;
    
    int comparacao = strcmp(nome, raiz->nome);
    
    if (comparacao < 0)
        raiz->esq = remover(raiz->esq, nome);
    else if (comparacao > 0)
        raiz->dir = remover(raiz->dir, nome);
    else {
        // caso 1: nó com zero ou um filho
        if (raiz->esq == NULL || raiz->dir == NULL) {
            struct treeNode *temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        }
        // caso 2: nó com dois filhos
        else {
            struct treeNode *temp = menorValor(raiz->dir);
            raiz->Id = temp->Id;
            strcpy(raiz->nome, temp->nome);
            strcpy(raiz->email, temp->email);
            raiz->dir = remover(raiz->dir, temp->nome);
        }
    }

    if (raiz == NULL)
        return raiz;
        
    raiz->altura = maior(altura_NO(raiz->esq), altura_NO(raiz->dir)) + 1;
    
    int fb = fatorBalanceamento(raiz);
    
    // rebalanceamento
    if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoLL(raiz);
        
    if (fb > 1 && fatorBalanceamento(raiz->esq) < 0)
        return rotacaoLR(raiz);
        
    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoRR(raiz);
        
    if (fb < -1 && fatorBalanceamento(raiz->dir) > 0)
        return rotacaoRL(raiz);
        
    return raiz;
}

void imprimirEmOrdem(struct treeNode *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        
        printf("id: %-4d | nome: %-30s | email: %-30s\n", raiz->Id, raiz->nome, raiz->email);
        
        imprimirEmOrdem(raiz->dir);
    }
}

struct treeNode *buscarPorNome(struct treeNode *raiz, char nome[]) {
    if (raiz == NULL)
        return NULL;
    
    int comparacao = strcmp(nome, raiz->nome);
    
    if (comparacao == 0)
        return raiz;
    
    if (comparacao < 0)
        return buscarPorNome(raiz->esq, nome);
    
    return buscarPorNome(raiz->dir, nome);
}