//
// Created by gabri on 09/11/2023.
//

#ifndef DICIONARIO_DOMAIN_H
#define DICIONARIO_DOMAIN_H

typedef struct Palavra {
    char data[25];
    struct Palavra *left;
    struct Palavra *right;
} Palavra;
typedef struct Tree {
    int data;
    struct Tree* left;
    struct Tree* right;
} Tree;

#endif //DICIONARIO_DOMAIN_H
