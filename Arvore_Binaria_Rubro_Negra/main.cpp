#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu() {
    printf("\n========== menu ==========\n");
    printf("1. inserir produto\n");
    printf("2. buscar produto\n");
    printf("3. remover produto\n");
    printf("4. listar produtos\n");
    printf("5. sair\n");
    printf("escolha uma opcao: ");
}

// função auxiliar para listar produtos em ordem
void listarProdutos(TreeNode* no) {
    if (no == NULL) return;
    listarProdutos(no->esq);
    printf("ID: %d | nome: %s | quantidade: %d | valor: R$%.2f | cor: %s\n", no->Id, no->nome, no->quantidade, no->valor, no->cor == RED ? "vermelho" : "preto");
    listarProdutos(no->dir);
}

int main(){
    TreeNode* raiz = NULL;
    int opcao, id, quantidade;
    char nome[100];
    float valor;

    do {
        clearScreen();
        menu();
        scanf("%d", &opcao);
        limparBuffer();

        TreeNode* encontrado = NULL;
        TreeNode* antes = NULL;

        switch (opcao) {
            case 1:
                clearScreen();
                printf("========== inserir produto ==========\n");
                printf("digite o ID do produto: ");
                scanf("%d", &id);
                limparBuffer();

                printf("digite o nome do produto: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("digite a quantidade: ");
                scanf("%d", &quantidade);

                printf("digite o valor: ");
                scanf("%f", &valor);

                raiz = inserir(raiz, id, nome, quantidade, valor);
                printf("produto cadastrado com sucesso!\n");

                system("pause");
                break;
            
            case 2:
                clearScreen();
                printf("========== buscar produto ==========\n");
                printf("digite o ID do produto para buscar: ");
                scanf("%d", &id);

                encontrado = buscar(raiz, id);

                if (encontrado) {
                    printf("ID: %d | nome: %s | quantidade: %d | valor: R$%.2f | cor: %s\n", encontrado->Id, encontrado->nome, encontrado->quantidade, encontrado->valor, encontrado->cor == RED ? "vermelho" : "preto");
                } else {
                    printf("produto nao encontrado.\n");
                }

                system("pause");
                break;

            case 3:
                clearScreen();
                printf("========== remover produto ==========\n");
                printf("digite o ID do produto para remover: ");
                scanf("%d", &id);

                antes = buscar(raiz, id);

                if (antes) {
                    raiz = remover(raiz, id);
                    printf("produto removido com sucesso!\n");
                } else {
                    printf("produto nao encontrado.\n");
                }

                break;

            case 4:
                clearScreen();
                printf("========== listar produtos ==========\n");
                printf("produtos cadastrados (em ordem):\n");
                listarProdutos(raiz);
                system("pause");
                break;
                
            case 5:
                printf("saindo...\n");
                break;

            default:
                printf("opcao invalida!\n");
                break;
        }
        
    } while (opcao != 5);

    return 0;
}