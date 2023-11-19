#include "HashTable.h"
#include "domain.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "word_tree.c"

// FIXME: site para construcao da HashTable:
// https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus

// FIXME: se tudo der errado usar lista duplamente encadeada
// typedef struct Letra {
//     char data;
//     struct Letra *next;
//     struct Letra *prev;
//     Palavra *palavras;
// } Letra;

void inorder(Palavra *root) {
  if (root != NULL) {
    inorder(root->left);
    printf("%s\n", root->data);
    inorder(root->right);
  } else
    return;
}

// TODO: validar operações de hash table

int main() {

  // TESTES OPERAÇÕES HASH TABLE
  Tree *bTreeA = malloc(sizeof(Tree));
  bTreeA->data = 9;
  HashTable *ht = create_table(CAPACITY);
  ht_insert(ht, (char *)"A", bTreeA);
  Tree *tree = ht_search(ht, (char *)"A");
  tree->data = 4;
  print_search(ht, (char *)"A");
}

void showInterface(HashTable *table) {
  int userInput = -1;

  // TODO REVISAR OPERACOES POSSIVEIS
  while (userInput != 0) {
    printf("----------------- / * / -----------------\n");
    printf("----------- B-Tree Dictionary -----------\n");
    printf("----------------- / * / -----------------\n");
    printf("\n-------------- OPERACOES --------------\n");
    printf("  1) Incluir palavra no dicionário\n");
    printf("  2) Remover palavra do dicionário\n");
    printf("  3) Encontrar palavra\n");
    printf("  4) Contar palavras (retorna o número total de palavras)\n");
    // TODO: ocorrências de uma palavra ou de todas as palavras?
    printf("  5) Contar ocorrências (retorna o número total de ocorrências de "
           "palavras)\n");
    // TODO: opção de ordem A-Z ou Z-A
    printf("  6) Listar todas as palavras\n");
    printf("  7) Listar todas as palavras com uma inicial específica\n");
    printf("  8) Exibir palavra(s) com maior número de ocorrências\n");
    // Originalmente, com 1 única ocorrência
    printf("  9) Exibir palavra(s) em ordem alfabética com x número de "
           "ocorrências\n");
    // TODO: ??
    printf("  10) Exibir palavras usando percurso pré-fixado\n");
    printf("  0) Fechar o programa.\n");

    scanf("%d", &userInput);

    switch (userInput) {
    // breaks
    case 0:
      printf("\n\n\n\nEncerrando... \n\n\n\n");
      break;
    // add
    case 1: {
      printf("\n\n\n\nDigite a palavra a ser adicionada (até 24 letras): "
             "\n\n\n\n");
      char word[25] = "";
      scanf("%24s", word);
      // TODO: encontrar a árvore certa
      WordNode *wordTree;
      // ht_search(HashTable * table, char *key);
      insert_or_sum_word(wordTree, word);
      break;
    }
    // remove
    case 2: {
      printf(
          "\n\n\n\nDigite a palavra a ser removida (até 24 letras): \n\n\n\n");
      char word[25] = "";
      scanf("%24s", word);
      // TODO: encontrar a árvore certa
      WordNode *wordTree;
      // ht_search(HashTable * table, char *key);
      remove_word(wordTree, word);
      break;
    }
    // finds
    case 3: {
      printf("\n\n\n\nDigite a palavra encontrada (até 24 letras): \n\n\n\n");
      char word[25] = "";
      scanf("%24s", word);
      // TODO: encontrar a árvore certa
      WordNode *wordTree;
      // ht_search(HashTable * table, char *key);
      // TODO: find word
      break;
    }
    // Errors
    default: {
      printf("\n\n\n\nComando não reconhecido! \n\n\n\n");
      break;
    }
    }
  }
}
