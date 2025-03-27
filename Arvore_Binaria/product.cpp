#include <stdio.h>
#include "product.h"

void printProduct(Product product){
    printf("ID: %d\n", product.ID);
    printf("Nome: %s", product.name);
    printf("Preco: %.2f\n", product.price);
    printf("Estoque: %d\n", product.stock);
}
