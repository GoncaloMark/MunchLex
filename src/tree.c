/// \file   threading.c
/// \author Gonçalo Marques
/// \date   2023-05

#include "include/tree.h"

static char* strdup(const char* str) {
    size_t length = strlen(str) + 1;  // Include space for the null terminator
    char* duplicate = malloc(length);
    if (duplicate != NULL) {
        strcpy(duplicate, str);
    }
    return duplicate;
}

tree_t* createNode(token_type_t type, char* value) {
    tree_t* node = malloc(sizeof(tree_t));
    node->type = type;
    node->value = strdup(value);
    node->parent = NULL;
    node->children = NULL;
    node->next = NULL;
    return node;
}