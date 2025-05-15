#ifndef ARVORE_H
#define ARVORE_H

struct treeNode {
    int Id;
    char nome[100];
    char email[200];
    int altura;
    struct treeNode *esq;
    struct treeNode *dir;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

int getId();

int altura_NO(TreeNodePtr treePtr);
int maior(int a, int b);

TreeNodePtr novoNO(int Id, char nome[], char email[]);

TreeNodePtr rotacaoRR(TreeNodePtr raiz);
TreeNodePtr rotacaoLL(TreeNodePtr raiz);
TreeNodePtr rotacaoLR(TreeNodePtr raiz);
TreeNodePtr rotacaoRL(TreeNodePtr raiz);

int fatorBalanceamento(TreeNodePtr raiz);

TreeNodePtr inserir(TreeNodePtr treePtr, int Id, char nome[], char email[]);
TreeNodePtr menorValor(TreeNodePtr treePtr);
TreeNodePtr remover(TreeNodePtr treePtr, char nome[]);
TreeNodePtr buscarPorNome(TreeNodePtr raiz, char nome[]);

void imprimirEmOrdem(TreeNodePtr raiz);

#endif
