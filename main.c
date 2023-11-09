#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define CAPACITY 50000 // HashTable size

unsigned long hash_function(char* key) {
    unsigned long i = 0;

    for(int j = 0; key[j]; j++)
        i += key[j];
    return i % CAPACITY;
}

typedef struct Palavra {
    char data[25];
    struct Palavra *left;
    struct Palavra *right;
} Palavra;


typedef struct HT_item {
    char* key;
    Palavra *value;
} HT_item;
typedef struct LinkedList {
    HT_item* item;
    struct LinkedList* next;
} LinkedList;;
typedef struct HashTable {
    HT_item** items;
    LinkedList** overflow_buckets;
    int size;
    int count;
} HashTable;

HT_item* create_item(char *key, Palavra* value) {
    HT_item* item = (HT_item*) malloc(sizeof(HT_item));
    item->key = (char *) malloc(strlen(key) + 1);
    item->value = (Palavra*) malloc(sizeof(Palavra));
    strcpy(item->key, key);
    item->value = value;
    return item;
}
HashTable* create_table(int size) {
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (HT_item**) calloc(table->size, sizeof(HT_item*));

    for(int i = 0; i < table->size; i++)
        table->items[i] = NULL;

    return table;
}
void free_item(HT_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}
void free_table(HashTable* table) {
    for(int i = 0; i < table->size; i++) {
        HT_item* item = table->items[i];
        if(item != NULL)
            free_item(item);
    }
    free(table->items);
    free(table);
}
Palavra* HT_search(HashTable* table, char* key) {
    int index = hash_function(key);
    HT_item* item =  table->items[index];

    if(item != NULL) {
        if(strcpy(item->key, key) == 0)
            return item->value;
    }
    return NULL;
}

LinkedList* allocate_list()
{
    // Allocates memory for a LinkedList pointer.
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    return list;
}

LinkedList* linkedlist_insert(LinkedList* list, HT_item* item)
{
    // Inserts the item onto the LinkedList.
    if (!list)
    {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }
    else if (list->next == NULL)
    {
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList* temp = list;

    while (temp->next->next)
    {
        temp = temp->next;
    }

    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    return list;
}

HT_item * linkedlist_remove(LinkedList* list)
{
    // Removes the head from the LinkedList.
    // Returns the item of the popped element.
    if (!list)
        return NULL;

    if (!list->next)
        return NULL;

    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    HT_item* it = NULL;
    memcpy(temp->item, it, sizeof(HT_item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}

void free_linkedlist(LinkedList* list)
{
    LinkedList* temp = list;

    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}
void handle_collision(HashTable* table, unsigned long index, HT_item* item)
{
    LinkedList* head = table->overflow_buckets[index];

    if (head == NULL)
    {
        // Creates the list.
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else {
        // Insert to the list.
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
}
void HT_insert(HashTable* table, char* key, Palavra* value) {
    HT_item* item = create_item(key, value);
    int index = hash_function(key);
    HT_item* current_item = table->items[index];

    if(current_item == NULL) {
        if(table->count == table->size) {
            printf("HashTable is full. \n");
            free_item(item);
            return;
        }
        table->items[index] = item;
        table->count++;
    } else {
        if(strcmp(current_item->key, key) == 0) {
            table->items[index]->value = value;
            return;
        } else {
            handle_collision(table, index, item);
            return;
        }
    }
}
//FIXME: site para construcao da HashTable: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus

//FIXME: se tudo der errado usar lista duplamente encadeada
//typedef struct Letra {
//    char data;
//    struct Letra *next;
//    struct Letra *prev;
//    Palavra *palavras;
//} Letra;






int main() {
//    Letra *alfabeto = NULL;


}