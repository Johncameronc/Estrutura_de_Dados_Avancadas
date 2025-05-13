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
    printf("1. inserir usuario\n");
    printf("2. buscar usuario\n");
    printf("3. remover usuario\n");
    printf("4. listar usuarios\n");
    printf("5. sair\n");
    printf("escolha uma opcao: ");
}

int main() {
    TreeNodePtr raiz = NULL;
    TreeNodePtr usuario = NULL;
    int opcao, id;
    char nome[100], email[200];
    
    do {
        clearScreen();
        menu();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                clearScreen();
                printf("\n========== inserir usuario ==========\n");
                printf("\ndigite o id: ");
                scanf("%d", &id);
                limparBuffer();
                
                printf("digite o nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                printf("digite o email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = 0;
                
                raiz = inserir(raiz, id, nome, email);
                printf("\nusuario inserido com sucesso!\n");
                system("pause");
                break;
                
            case 2:
                clearScreen();
                printf("\n========== buscar usuario ==========\n");
                printf("\ndigite o nome para buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                usuario = buscarPorNome(raiz, nome);
                if (usuario != NULL) {
                    printf("\nusuario encontrado:\n");
                    printf("id: %d\n", usuario->Id);
                    printf("nome: %s\n", usuario->nome);
                    printf("email: %s\n", usuario->email);
                } else {
                    printf("\nusuario nao encontrado!\n");
                }
                system("pause");
                break;
                
            case 3:
                clearScreen();
                printf("\n========== remover usuario ==========\n");
                printf("\ndigite o nome para remover: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                raiz = remover(raiz, nome);
                printf("\nusuario removido com sucesso!\n");
                system("pause");
                break;
                
            case 4:
                clearScreen();
                printf("\n=== lista de usuarios ===\n");
                if (raiz == NULL) {
                    printf("arvore vazia!\n");
                } else {
                    imprimirEmOrdem(raiz);
                }
                system("pause");
                break;
                
            case 5:
                printf("\nsaindo do programa...\n");
                break;
                
            default:
                printf("\nopcao invalida!\n");
        }
        
    } while (opcao != 5);
    
    return 0;
}
