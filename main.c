#include "stdio.h"
#include "stdlib.h"

typedef struct Palavra {
    char data[25];
    struct Palavra *left;
    struct Palavra *right;
} Palavra;

typedef struct Letra {
    char data;
    struct Letra *next;
    struct Letra *prev;
    Palavra *palavras;
} Letra;