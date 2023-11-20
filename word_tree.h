#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Each word node carries a word and an ocurrences number
// to the left of the node there should be an lexicographically smaller word if
// any
// to the right of the node there should be an lexicographically bigger word
// if any
// TODO: adaptar à hash table
typedef struct WordNode {
    char word[25];
    int occurences;
    struct WordNode *left;
    struct WordNode *right;
} WordNode;

WordNode *create_word(char word[25]) {
    WordNode *newWord = (WordNode *) malloc(sizeof(WordNode));
    strcpy(newWord->word, word);
    newWord->occurences = 1;
    newWord->left = NULL;
    newWord->right = NULL;
    printf("arvore criada \n"); //FIXME: remover após debugar;
    return newWord;
}

// TODO: test
int is_alphabetically_after(char wordA[25], char wordB[25]) {
    // strcmp
    // returns >0 if A is lexicographically bigger than B
    // returns 0 if A is lexicographically equal to B
    // returns <0 if A is lexicographically smaller than B
    return strcmp(wordA, wordB);
}

void print_word_node(WordNode *node) {
    printf("\n%s - %d ocorrências!\n", node->word, node->occurences);
}

// TODO: test
// prints all in given order
void print_tree(WordNode *node, int commonOrder) {
    if (node != NULL) {
        // if common order is true, prints A-Z
        if (commonOrder) {
            // the leftest node is the lexicographically smaller, or first
            print_tree(node->left, commonOrder);
            print_word_node(node);
            print_tree(node->right, commonOrder);
        }
            // else, prints Z-A
        else {
            // the rightest node is the lexicographically bigger, or last
            print_tree(node->right, commonOrder);
            print_word_node(node);
            print_tree(node->left, commonOrder);
        }
    }
}

// TODO: transform two functions in a run through function with callback?
// -------

// TODO: test
void sums_all_words(WordNode *node, int *counter) {
    if (node != NULL) {

        counter++;
        sums_all_words(node->left, counter);
        sums_all_words(node->right, counter);
    }
}

// TODO: test
void sums_all_words_occurrences(WordNode *node, int *counter) {
    if (node != NULL) {

        counter += node->occurences;
        sums_all_words(node->left, counter);
        sums_all_words(node->right, counter);
    }
}
// -------

// used to print one word node
WordNode *find_node(WordNode *node, char word[25]) {
    if (node == NULL) {
        printf("\nEssa palavra ainda nao foi inserida!\n");
        return node;
    }

    int conditional = is_alphabetically_after(word, node->word);

    if (conditional > 0) {
        node->right = find_node(node, word);
    } else if (conditional < 0) {
        node->left = find_node(node, word);
    }
        // found
    else {
        printf("\nA palavra %s foi encontrada, possuindo %d ocorrências!\n",
               node->word, node->occurences);
    }

    return node;
}

// TODO: test
// this will be used to list same occurrence number nodes
WordNode *insert_node(WordNode *node, WordNode *insertNode) {
    if (node == NULL) {
        return insertNode;
    }

    int conditional = is_alphabetically_after(insertNode->word, node->word);

    if (conditional > 0) {
        node->right = insert_node(node, insertNode);
    } else if (conditional < 0) {
        node->left = insert_node(node, insertNode);
    }

    return node;
}

// TODO: test
// finds biggest node of tree
WordNode *find_biggest_occurrence_number_node(WordNode *node) {
    WordNode *biggest;
    if (node != NULL) {
        // Uses new tree to copy same occurrence number nodes
        if (biggest == NULL) {
            biggest = create_word(node->word);
        } else {
            // If node is bigger than biggest, overwrite biggest with node
            if (biggest->occurences < node->occurences) {
                biggest = node;
            }
                // If node is equal with biggest, adds node to biggest tree
            else if (biggest->occurences == node->occurences) {
                insert_node(biggest, node);
            }
        }

        find_biggest_occurrence_number_node(node->right);
        find_biggest_occurrence_number_node(node->left);
    }

    return biggest;
}

// TODO: test
WordNode *insert_or_sum_word(WordNode *node, char word[25]) {
    if (node == NULL) {
        printf("Arvore ainda nao criada, criando nova arvore...\n");
        return create_word(word);
    }

    int conditional = is_alphabetically_after(word, node->word);

    if (conditional > 0) {
        node->right = insert_or_sum_word(node, word);
    } else if (conditional < 0) {
        node->left = insert_or_sum_word(node, word);
    } else {
        node->occurences++;
    }

    return node;
}

// TODO: test
WordNode *remove_word(WordNode *node, char word[25]) {
    if (node == NULL) {
        return node;
    }

    int conditional = is_alphabetically_after(word, node->word);

    if (conditional > 0) {
        node->right = remove_word(node, word);
    } else if (conditional < 0) {
        node->left = remove_word(node, word);
    }
        // Node to be deleted found
    else {
        // Node with only one child or no child
        if (node->left == NULL) {
            WordNode *temporary = node->right;
            free(node);
            return temporary;
        } else if (node->right == NULL) {
            WordNode *temporary = node->left;
            free(node);
            return temporary;
        }

        // Node with two children: Get the inorder successor (smallest in the right
        // subtree)
        WordNode *temporary;
        WordNode *loop = node->right;
        while (loop->left != NULL) {
            loop = loop->left;
        }
        temporary = loop;

        // Copy the inorder successor's data to this node
        strcpy(temporary->word, node->word);
        node->occurences = temporary->occurences;

        // Delete the inorder successor
        node->right = remove_word(node->right, temporary->word);
    }

    return node;
}
