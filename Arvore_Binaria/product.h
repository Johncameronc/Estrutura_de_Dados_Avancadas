#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct product {
    int ID;
    char name[100];
    float price;
    int stock;
} Product;

void printProduct(Product product);

#endif
