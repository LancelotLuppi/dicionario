#include "HashTable.h"
#include "domain.h"
#include "stdio.h"
#include "stdlib.h"

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
      printf("\n\n\n\nDigite a palavra a ser adicionada (ate 24 letras): \n");
      char word[25];
      scanf("%s", word);
      char key[2];
      key[0] = word[0];
      key[1] = '\0';
      WordNode *node = ht_search(table, key);
      if (node == NULL) {
        node = insert_or_sum_word(node, word);
        ht_insert(table, key, node);
      } else {
        insert_or_sum_word(node, word);
      }
      break;
    }
      // remove
      // FIXME: when there is only one word and it gets deleted, the tree
      // continues with a ghost item
    case 2: {
      printf(
          "\n\n\n\nDigite a palavra a ser removida (até 24 letras): \n\n\n\n");
      char word[25] = "";
      scanf("%24s", word);
      char key[2];
      key[0] = word[0];
      key[1] = '\0';
      WordNode *wordTree = ht_search(table, key);
      remove_word(wordTree, word);
      break;
    }
      // finds
    case 3: {
      printf("\n\n\n\nDigite a palavra a ser encontrada (até 24 letras): "
             "\n\n\n\n");
      char word[25] = "";
      scanf("%24s", word);
      char key[2];
      key[0] = word[0];
      key[1] = '\0';
      WordNode *wordTree = ht_search(table, key);
      find_node(wordTree, word);
      break;
    }
      // sums all words
    case 4: {
      int counter = 0;
      for_each_hash_table_item_with_counter(table, &sums_all_words, &counter);
      printf("\nO número total de palavras é %d\n\n", counter);
      break;
    }
      // sums all words occurrences
    case 5: {
      int counter = 0;
      // Will sum to counter all words occurrences of given tree
      for_each_hash_table_item_with_counter(table, &sums_all_words_occurrences,
                                            &counter);
      printf("\nO número total de ocorrências de todas as palavras é %d\n\n",
             counter);
      break;
    }
      // prints all words with given order
    case 6: {
      printf("\n\n\n\nDigite a ordem para listar as palavras (1 para A-Z 0 "
             "para Z-A): "
             "\n\n\n\n");
      int order = 0;
      scanf("%d", &order);

      for_each_hash_table_item(table, &print_tree, order);

      break;
    }
      // prints all words with given order and given initial
    case 7: {
      printf("\n\n\n\nDigite a inicial das palavras a serem listadas\n\n\n\n");
      char key[2];
      scanf(" %c", &key[0]);
      key[1] = '\0';
      printf("\n\n\n\nDigite a ordem para listar as palavras (1 para A-Z 0 "
             "para Z-A): "
             "\n\n\n\n");
      int order = 0;
      scanf("%d", &order);
      WordNode *wordTree = ht_search(table, key);

      print_tree(wordTree, order);
      break;
    }
      // Finds and prints word (or words) with biggest number of occurrences
    case 8: {
      // will return a new tree with all the biggest occurences nodes
      // (nodes with same number of occurences)
      WordNode *biggestTree = for_each_hash_table_item_returns_node(
          table, &find_biggest_occurrence_number_node);

      print_tree(biggestTree, 0);
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

int main() {
  HashTable *table = create_table(CAPACITY);
  showInterface(table);
}
