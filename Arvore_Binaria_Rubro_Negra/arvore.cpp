#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TreeNode* NULL_LEAF = NULL;

TreeNode* criarNo(int Id, char nome[], int quantidade, float valor) {
    TreeNode* novo = (TreeNode*)malloc(sizeof(TreeNode));
    novo->Id = Id;
    strcpy(novo->nome, nome);
    novo->quantidade = quantidade;
    novo->valor = valor;
    novo->cor = RED;
    novo->esq = novo->dir = novo->pai = NULL;
    return novo;
}

TreeNode* rotacaoRR(TreeNode* raiz, TreeNode* x) {
    TreeNode* y = x->dir;

    x->dir = y->esq;

    if (y->esq != NULL)
        y->esq->pai = x;
        
    y->pai = x->pai;

    if (x->pai == NULL)
        raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;

    return raiz;
}

TreeNode* rotacaoLL(TreeNode* raiz, TreeNode* y) {
    TreeNode* x = y->esq;

    y->esq = x->dir;

    if (x->dir != NULL)
        x->dir->pai = y;

    x->pai = y->pai;

    if (y->pai == NULL)
        raiz = x;
    else if (y == y->pai->dir)
        y->pai->dir = x;
    else
        y->pai->esq = x;

    x->dir = y;
    y->pai = x;

    return raiz;
}

TreeNode* inserirBST(TreeNode* raiz, TreeNode* novo) {
    if (raiz == NULL)
        return novo;

    if (novo->valor < raiz->valor) {
        raiz->esq = inserirBST(raiz->esq, novo);
        raiz->esq->pai = raiz;
    } else if (novo->valor > raiz->valor) {
        raiz->dir = inserirBST(raiz->dir, novo);
        raiz->dir->pai = raiz;
    }

    return raiz;
}

TreeNode* corrigirInsercao(TreeNode* raiz, TreeNode* no) {
    TreeNode* tio;
    while (no != raiz && no->pai->cor == RED) {
        if (no->pai == no->pai->pai->esq) {
            tio = no->pai->pai->dir;
            if (tio != NULL && tio->cor == RED) {
                no->pai->cor = BLACK;
                tio->cor = BLACK;
                no->pai->pai->cor = RED;
                no = no->pai->pai;
            } else {
                if (no == no->pai->dir) {
                    no = no->pai;
                    raiz = rotacaoRR(raiz, no);
                }
                no->pai->cor = BLACK;
                no->pai->pai->cor = RED;
                raiz = rotacaoLL(raiz, no->pai->pai);
            }
        } else {
            tio = no->pai->pai->esq;
            if (tio != NULL && tio->cor == RED) {
                no->pai->cor = BLACK;
                tio->cor = BLACK;
                no->pai->pai->cor = RED;
                no = no->pai->pai;
            } else {
                if (no == no->pai->esq) {
                    no = no->pai;
                    raiz = rotacaoLL(raiz, no);
                }
                no->pai->cor = BLACK;
                no->pai->pai->cor = RED;
                raiz = rotacaoRR(raiz, no->pai->pai);
            }
        }
    }
    raiz->cor = BLACK;
    return raiz;
}

TreeNode* inserir(TreeNode* raiz, int Id, char nome[], int quantidade, float valor) {
    TreeNode* novo = criarNo(Id, nome, quantidade, valor);
    raiz = inserirBST(raiz, novo);
    return corrigirInsercao(raiz, novo);
}

void emOrdem(TreeNode* raiz) {
    if (raiz == NULL) return;

    emOrdem(raiz->esq);
    printf("%d (%s) ", raiz->valor, raiz->cor == RED ? "R" : "B");
    emOrdem(raiz->dir);
}

TreeNode *criarFolhaNula() {
    TreeNode* folha = (TreeNode*)malloc(sizeof(TreeNode));

    folha->cor = BLACK;
    folha->valor = 0;
    folha->esq = folha->dir = folha->pai = NULL;

    return folha;
}

TreeNode* buscar(TreeNode* raiz, int Id) {
    if (raiz == NULL || raiz->Id == Id)
        return raiz;
    if (Id < raiz->Id)
        return buscar(raiz->esq, Id);
    else
        return buscar(raiz->dir, Id);
}

void transplantar(TreeNode** raiz, TreeNode* u, TreeNode* v) {
    if (u->pai == NULL)
        *raiz = v;
    else if (u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;

    if (v != NULL)
        v->pai = u->pai;
}

TreeNode* minimo(TreeNode* no) {
    while (no->esq != NULL)
        no = no->esq;
    return no;
}

TreeNode* corrigirRemocao(TreeNode* raiz, TreeNode* x) {
    while (x != raiz && (x == NULL || x->cor == BLACK)) {
        if (x == x->pai->esq) {
            TreeNode* w = x->pai->dir; // irm�o de x

            // Caso 1: irm�o vermelho
            if (w->cor == RED) {
                w->cor = BLACK;
                x->pai->cor = RED;
                raiz = rotacaoRR(raiz, x->pai);
                w = x->pai->dir;
            }

            // Caso 2: irm�o e filhos pretos
            if ((w->esq == NULL || w->esq->cor == BLACK) &&
                (w->dir == NULL || w->dir->cor == BLACK)) {
                w->cor = RED;
                x = x->pai;
            } else {
                // Caso 3: irm�o preto, filho esquerdo vermelho
                if (w->dir == NULL || w->dir->cor == BLACK) {
                    if (w->esq != NULL && w->esq->cor == RED) w->esq->cor = BLACK;
                    w->cor = RED;
                    raiz = rotacaoLL(raiz, w);
                    w = x->pai->dir;
                }

                // Caso 4: irm�o preto, filho direito vermelho
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                if (w->dir != NULL && w->dir->cor == RED) w->dir->cor = BLACK;
                raiz = rotacaoRR(raiz, x->pai);
                x = raiz;
            }
        } else {
            // Mesma l�gica, mas espelhada para x ser filho da direita
            TreeNode* w = x->pai->esq;

            if (w->cor == RED) {
                w->cor = BLACK;
                x->pai->cor = RED;
                raiz = rotacaoLL(raiz, x->pai);
                w = x->pai->esq;
            }

            if ((w->esq == NULL || w->esq->cor == BLACK) &&
                (w->dir == NULL || w->dir->cor == BLACK)) {
                w->cor = RED;
                x = x->pai;
            } else {
                if (w->esq == NULL || w->esq->cor == BLACK) {
                    if (w->dir != NULL && w->dir->cor == RED) w->dir->cor = BLACK;
                    w->cor = RED;
                    raiz = rotacaoRR(raiz, w);
                    w = x->pai->esq;
                }

                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                if (w->esq != NULL && w->esq->cor == RED) w->esq->cor = BLACK;
                raiz = rotacaoLL(raiz, x->pai);
                x = raiz;
            }
        }
    }

    if (x != NULL)
        x->cor = BLACK;

    return raiz;
}

TreeNode* remover(TreeNode* raiz, int Id) {
    TreeNode* z = buscar(raiz, Id);  // N� a ser removido
    if (z == NULL) return raiz;     // N�o encontrado

    TreeNode *y = z;                    // N� que ser� efetivamente removido
    TreeNode *x;                        // N� que tomar� o lugar (ou NULL_LEAF)
    Color cor_original = y->cor;    // Precisamos saber a cor original

    if (z->esq == NULL) {
        x = z->dir;
        transplantar(&raiz, z, z->dir);
    } else if (z->dir == NULL) {
        x = z->esq;
        transplantar(&raiz, z, z->esq);
    } else {
        y = minimo(z->dir);
        cor_original = y->cor;
        x = y->dir;

        if (y->pai == z) {
            if (x != NULL) x->pai = y;
        } else {
            transplantar(&raiz, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }

        transplantar(&raiz, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }

    free(z);

    if (cor_original == BLACK) {
        raiz = corrigirRemocao(raiz, x);
    }

    return raiz;
}