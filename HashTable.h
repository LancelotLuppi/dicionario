#ifndef DICIONARIO_HASHTABLE_H
#define DICIONARIO_HASHTABLE_H

#include "domain.h"
#include "word_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 50000 // Size of the HashTable.

unsigned long hash_function(char *str) {
  /* unsigned long i = 0; */
  /**/
  /* for (int j = 0; str[j]; j++) */
  /*   i += str[j]; */

  return str[0] % CAPACITY;
}

// Defines the HashTable item.
typedef struct Ht_item {
  char *key;
  WordNode *value;
} Ht_item;

// Defines the LinkedList.
typedef struct LinkedList {
  Ht_item *item;
  struct LinkedList *next;
} LinkedList;

// Defines the HashTable.
typedef struct HashTable {
  // Contains an array of pointers to items.
  Ht_item **items;
  LinkedList **overflow_buckets;
  int size;
  int count;
} HashTable;

LinkedList *allocate_list() {
  // Allocates memory for a LinkedList pointer.
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  return list;
}

// Define a callback function type
typedef void (*CallbackFunc)(WordNode *, int);
typedef WordNode *(*CallbackFuncReturnsNode)(WordNode *, WordNode *, int);
typedef void (*CallbackFuncWithCounter)(WordNode *, int *);

void for_each_hash_table_item(HashTable *table, CallbackFunc function,
                              int order) {
  if (table->items) {
    if (order) {
      for (int i = 0; i < table->size; i++) {
        if (table->items[i]) {
          function(table->items[i]->value, order);
        }
      }
    } else {
      for (int i = table->size; i >= 0; i--) {
        if (table->items[i]) {
          function(table->items[i]->value, order);
        }
      }
    }
  }
}

WordNode *
for_each_hash_table_item_returns_node(HashTable *table,
                                      CallbackFuncReturnsNode function, int x) {
  WordNode *biggest = NULL;

  if (table->items) {
    for (int i = table->size; i >= 0; i--) {
      if (table->items[i]) {
        biggest = function(table->items[i]->value, biggest, x);
      }
    }
  }

  return biggest;
}

void for_each_hash_table_item_with_counter(HashTable *table,
                                           CallbackFuncWithCounter function,
                                           int *counter) {
  if (table->items) {
    for (int i = 0; i < table->size; i++) {
      if (table->items[i]) {
        function(table->items[i]->value, counter);
      }
    }
  }
}

LinkedList *linkedlist_insert(LinkedList *list, Ht_item *item) {
  // Inserts the item onto the LinkedList.
  if (!list) {
    LinkedList *head = allocate_list();
    head->item = item;
    head->next = NULL;
    list = head;
    return list;
  } else if (list->next == NULL) {
    LinkedList *node = allocate_list();
    node->item = item;
    node->next = NULL;
    list->next = node;
    return list;
  }

  LinkedList *temp = list;

  while (temp->next->next) {
    temp = temp->next;
  }

  LinkedList *node = allocate_list();
  node->item = item;
  node->next = NULL;
  temp->next = node;
  return list;
}

Ht_item *linkedlist_remove(LinkedList *list) {
  // Removes the head from the LinkedList.
  // Returns the item of the popped element.
  if (!list)
    return NULL;

  if (!list->next)
    return NULL;

  LinkedList *node = list->next;
  LinkedList *temp = list;
  temp->next = NULL;
  list = node;
  Ht_item *it = NULL;
  memcpy(temp->item, it, sizeof(Ht_item));
  free(temp->item->key);
  free(temp->item->value);
  free(temp->item);
  free(temp);
  return it;
}

void free_linkedlist(LinkedList *list) {
  LinkedList *temp = list;

  while (list) {
    temp = list;
    list = list->next;
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
  }
}

LinkedList **create_overflow_buckets(HashTable *table) {
  // Create the overflow buckets; an array of LinkedLists.
  LinkedList **buckets =
      (LinkedList **)calloc(table->size, sizeof(LinkedList *));

  for (int i = 0; i < table->size; i++)
    buckets[i] = NULL;

  return buckets;
}

void free_overflow_buckets(HashTable *table) {
  // Free all the overflow bucket lists.
  LinkedList **buckets = table->overflow_buckets;

  for (int i = 0; i < table->size; i++)
    free_linkedlist(buckets[i]);

  free(buckets);
}

Ht_item *create_item(char *key, WordNode *value) {
  // Creates a pointer to a new HashTable item.
  printf("Criando item na tabela hash...\n");
  Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
  item->key = (char *)malloc(strlen(key) + 1);
  item->value = (WordNode *)malloc(sizeof(WordNode));
  strcpy(item->key, key);
  item->value = value;
  printf("\nkeeyyy: %s\n\n", item->key);
  printf("Item criado na tabela\n");
  return item;
}

HashTable *create_table(int size) {
  // Creates a new HashTable.
  HashTable *table = (HashTable *)malloc(sizeof(HashTable));
  table->size = size;
  table->count = 0;
  table->items = (Ht_item **)calloc(table->size, sizeof(Ht_item *));

  for (int i = 0; i < table->size; i++)
    table->items[i] = NULL;

  table->overflow_buckets = create_overflow_buckets(table);

  return table;
}

void free_item(Ht_item *item) {
  // Frees an item.
  free(item->key);
  free(item->value);
  free(item);
}

void free_table(HashTable *table) {
  // Frees the table.
  for (int i = 0; i < table->size; i++) {
    Ht_item *item = table->items[i];

    if (item != NULL)
      free_item(item);
  }

  // Free the overflow bucket lists and its items.
  free_overflow_buckets(table);
  free(table->items);
  free(table);
}

void handle_collision(HashTable *table, unsigned long index, Ht_item *item) {
  LinkedList *head = table->overflow_buckets[index];

  if (head == NULL) {
    // Creates the list.
    head = allocate_list();
    head->item = item;
    table->overflow_buckets[index] = head;
    return;
  } else {
    // Insert to the list.
    table->overflow_buckets[index] = linkedlist_insert(head, item);
    return;
  }
}

void ht_insert(HashTable *table, char *key, WordNode *value) {
  // Creates the item.
  Ht_item *item = create_item(key, value);

  // Computes the index.
  int index = hash_function(key);
  printf("Item criado no index %d\n", index); // FIXME: remover após debugar

  Ht_item *current_item = table->items[index];

  if (current_item == NULL) {
    // Key does not exist.
    if (table->count == table->size) {
      // HashTable is full.
      printf("Insert Error: Hash Table is full\n");
      free_item(item);
      return;
    }

    // Insert directly.
    table->items[index] = item;
    table->count++;
  } else {
    // Scenario 1: Update the value.
    if (strcmp(current_item->key, key) == 0) {
      table->items[index]->value = value;
      return;
    } else {
      // Scenario 2: Handle the collision.
      handle_collision(table, index, item);
      return;
    }
  }
}

WordNode *ht_search(HashTable *table, char *key) {
  // Searches for the key in the HashTable.
  // Returns NULL if it doesn't exist.
  printf("Iniciando busca na hash table, chave utilizada: %c\n",
         *key); // FIXME: remover após debugar
  int index = hash_function(key);
  printf("Item pesquisado no index %d\n", index); // FIXME: remover após debugar
  Ht_item *item = table->items[index];
  LinkedList *head = table->overflow_buckets[index];

  // Provide only non-NULL values.
  if (item != NULL) {
    if (strcmp(item->key, key) == 0) {
      printf("Item encontrado\n\n"); // FIXME: remover após debugar
      return item->value;
    }

    if (head == NULL) {
      printf("Head null.\n\n"); // FIXME: remover após debugar
    }
    return NULL;

    item = head->item;
    head = head->next;
  }
  printf("Item nao criado.\n\n"); // FIXME: remover após debugar
  return NULL;
}

void ht_delete(HashTable *table, char *key) {
  // Deletes an item from the table.
  int index = hash_function(key);
  Ht_item *item = table->items[index];
  LinkedList *head = table->overflow_buckets[index];

  if (item == NULL) {
    // Does not exist.
    return;
  } else {
    if (head == NULL && strcmp(item->key, key) == 0) {
      // Collision chain does not exist.
      // Remove the item.
      // Set table index to NULL.
      table->items[index] = NULL;
      free_item(item);
      table->count--;
      return;
    } else if (head != NULL) {
      // Collision chain exists.
      if (strcmp(item->key, key) == 0) {
        // Remove this item.
        // Set the head of the list as the new item.
        free_item(item);
        LinkedList *node = head;
        head = head->next;
        node->next = NULL;
        table->items[index] = create_item(node->item->key, node->item->value);
        free_linkedlist(node);
        table->overflow_buckets[index] = head;
        return;
      }

      LinkedList *curr = head;
      LinkedList *prev = NULL;

      while (curr) {
        if (strcmp(curr->item->key, key) == 0) {
          if (prev == NULL) {
            // First element of the chain.
            // Remove the chain.
            free_linkedlist(head);
            table->overflow_buckets[index] = NULL;
            return;
          } else {
            // This is somewhere in the chain.
            prev->next = curr->next;
            curr->next = NULL;
            free_linkedlist(curr);
            table->overflow_buckets[index] = head;
            return;
          }
        }

        curr = curr->next;
        prev = curr;
      }
    }
  }
}

void print_search(HashTable *table, char *key) {
  WordNode *val;

  if ((val = ht_search(table, key)) == NULL) {
    printf("Key:%s does not exist\n", key);
    return;
  } else {
    printf("key: %s, value: %s\n", key, val->word);
  }
}

void print_table(HashTable *table) {
  printf("\nHash Table\n-------------------\n");

  for (int i = 0; i < table->size; i++) {
    if (table->items[i]) {
      printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key,
             table->items[i]->value->word);
    }
  }

  printf("-------------------\n\n");
}

char *get_key(char c) {
  printf("Gerando chave \n"); // FIXME remover apos debugar
  char key[2];
  key[0] = c;
  printf("char ok \n"); // FIXME remover apos debugar
  key[1] = '\n';
  printf("final ok \n"); // FIXME remover apos debugar
  return key;
}

#endif // DICIONARIO_HASHTABLE_H
