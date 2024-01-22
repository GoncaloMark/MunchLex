/// \file   tree.c
/// \author Gonçalo Marques
/// \date   2024-01

#include "include/tree.h"
#include <string.h>

tree_t* createNode(token_type_t type, const char* start, size_t length) {
    tree_t* node = malloc(sizeof(tree_t));
    if (node == NULL)
        return NULL;

    node->content = malloc(length + 1);
    if (node->content == NULL)
        return NULL;
    strncpy(node->content, start, length);
    node->content[length] = '\0';

    node->type = type;
    node->parent = NULL;
    node->children = NULL;
    node->children_count = 0;
    return node;
}

void addChild(tree_t* parent, tree_t* child){
    size_t newCount = parent->children_count + 1;
    tree_t** newChildren = realloc(parent->children, newCount * sizeof(tree_t*));

    if (newChildren == NULL) {
        return;
    }

    parent->children = newChildren;
    parent->children[parent->children_count] = child;
    parent->children_count = newCount;
}

void deleteTree(tree_t* head) {
    if (head == NULL) {
        return;
    }

    for (size_t i = 0; i < head->children_count; ++i) {
        deleteTree(head->children[i]);
    }

    if (head->children != NULL) {
        free(head->children);
    }

    if (head->content != NULL) {
        free(head->content);
    }

    free(head);
}

void printTree(const tree_t* node, int depth, char* file) {
    if (node == NULL) {
        return;
    }

    if(file == NULL){
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }

        printf("Type: %d, Content: %s\n", node->type, node->content ? node->content : "(null)");

        for (size_t i = 0; i < node->children_count; i++) {
            printTree(node->children[i], depth + 1, NULL);
        }

        return;
    }

    FILE* fp = fopen(file, "a");
    if (fp == NULL) {
        perror("Unable to open log file");
        return;
    }

    for (int i = 0; i < depth; i++) {
        fprintf(fp, "  ");
    }

    fprintf(fp, "Type: %d, Content: %s\n", node->type, node->content ? node->content : "(null)");
    fclose(fp);

    for (size_t i = 0; i < node->children_count; i++) {
        printTree(node->children[i], depth + 1, file); //TODO: optimize this since it will keep opening and closing the file :(
    }

    return;
}


