#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "HashTable.h"
#include "domain.h"


//FIXME: site para construcao da HashTable: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus

//FIXME: se tudo der errado usar lista duplamente encadeada
//typedef struct Letra {
//    char data;
//    struct Letra *next;
//    struct Letra *prev;
//    Palavra *palavras;
//} Letra;


Palavra* createWord(char data[]) {
    Palavra *newWord = (Palavra*) malloc(sizeof(Palavra));
    strcpy(newWord->data, data);
    newWord->left = NULL;
    newWord->right = NULL;
    return newWord;
}
//FIXME: comparar a posição no alfabeto entre duas Strings
//Palavra* insert(Palavra *root, char[] data) {
//    if(root == NULL)
//        return createWord(data);
//    if(num < root->data)
//        root->left = insert(root->left, num);
//    else if(num > root->data)
//        root->right = insert(root->right, num);
//    return root;
//}
void inorder(Palavra *root) {
    if(root != NULL) {
        inorder(root->left);
        printf("%s\n", root->data);
        inorder(root->right);
    }
    else
        return;
}

//TODO: validar operações de hash table

int main() {

}