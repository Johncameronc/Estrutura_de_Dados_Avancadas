#ifndef ARVORE_H
#define ARVORE_H

typedef enum { RED, BLACK } Color;

struct treeNode {
    int Id;
    char nome[100];
    int quantidade;
    float valor;

    Color cor;
    struct treeNode *esq;
    struct treeNode *dir;
    struct treeNode *pai;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

TreeNodePtr criarNo(int Id, char nome[], int quantidade, float valor);

// rotacao simples esquerda
TreeNodePtr rotacaoRR(TreeNodePtr raiz);

// rotacao simples direita
TreeNodePtr rotacaoLL(TreeNodePtr raiz);

// rotacao dupla à esquerda-direita
TreeNodePtr rotacaoLR(TreeNodePtr raiz);

// rotacao dupla à direita-esquerda
TreeNodePtr rotacaoRL(TreeNodePtr raiz);

TreeNodePtr inserirBST(TreeNodePtr *raiz, TreeNodePtr *novo);
TreeNodePtr corrigirInsercao(TreeNodePtr *raiz, TreeNodePtr *no);
TreeNode* inserir(TreeNode* raiz, int Id, char nome[], int quantidade, float valor);

void emOrdem(TreeNodePtr raiz);

extern TreeNode* NULL_LEAF;
TreeNode *criarFolhaNula();
TreeNode* buscar(TreeNode* raiz, int Id);

void transplantar(TreeNodePtr** raiz, TreeNodePtr* u, TreeNodePtr* v);
TreeNodePtr *minimo(TreeNodePtr* no);

TreeNodePtr* corrigirRemocao(TreeNodePtr* raiz, TreeNodePtr* x);
TreeNode* remover(TreeNode* raiz, int Id); 

#endif