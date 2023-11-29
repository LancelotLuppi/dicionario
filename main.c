#include "HashTable.h"
#include "domain.h"
#include "stdio.h"
#include "stdlib.h"

// FIXME: site base para construcao da HashTable:
// https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus

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
    printf("  5) Contar ocorrências (retorna o número total de ocorrências de "
           "palavras)\n");
    printf("  6) Listar todas as palavras\n");
    printf("  7) Listar todas as palavras com uma inicial específica\n");
    printf("  8) Exibir palavra(s) com maior número de ocorrências\n");
    printf("  9) Exibir palavra(s) com x número de "
           "ocorrências\n");
    printf("  10) Exibir arvore usando percurso pré-fixado\n");
    printf("  11) Exibir dicionario usando percurso pré-fixado\n");
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

      if (!(wordTree->occurences)) {
        ht_delete(table, key);
      }
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
          table, &find_biggest_occurrence_number_node, 0);

      print_tree(biggestTree, 0);
      break;
    }
      // Finds and prints word (or words) with x number of occurrences
    case 9: {
      printf("\n\n\n\nDigite o número de ocorrências das palavras a serem "
             "listadas\n\n\n\n");

      int x = 0;
      scanf("%d", &x);

      for_each_hash_table_item(table, &find_x_occurrence_number_node, x);

      break;
    }
    case 10: {
        printf("\n\n\n\nPercursão pré-fixadan a partir de inicial\n\n");
        printf("Informe uma letra: \n");
        char key[2];
        scanf(" %c", &key[0]);
        key[1] = '\0';
        WordNode *wordTree = ht_search(table, key);
        if(wordTree == NULL) {
            printf("Arvore vazia.");
            break;
        }
        preorder_print(wordTree, 1);
        printf("Fim da lista.\n");
        break;
      }
      preorder_print(wordTree, 1);
      printf("Fim da lista.\n");
      break;
    }
    case 11: {
        printf("\n\n\n\nPercursão pré-fixada de todo dicionario\n\n");
        printf("\n\nDigite a ordem para listar as palavras (1 para A-Z 0 "
               "para Z-A): "
               "\n\n");
        int order = 0;
        scanf("%d", &order);
        for_each_hash_table_item(table, &preorder_print, order);
        printf("Fim da lista.\n");
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
