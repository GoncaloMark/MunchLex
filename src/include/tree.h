/// \file   parser.h
/// \author Gonçalo Marques
/// \date   2024-01

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "parser.h"

/// @brief  - TreeNode type holds information regarding a Node.
typedef struct TreeNode {
    token_type_t type;
    char* content;
    tree_t* parent;
    size_t children_count;
    tree_t** children;
} tree_t;

/// @brief              - Returns a pointer to a tree_t struct, after parsing the line it constructs the node element.
/// @param type         - Type of the Token.
/// @param value        - Value to be written to the content of the Node.
/// @return             - tree_t* (pointer to an allocated tree_t struct)
tree_t* createNode(token_type_t type, char* value);

void addChild(tree_t* parent, tree_t* child);

void deleteTree(tree_t** head);

tree_t* searchNodeType(token_type_t type);

tree_t* searchNodeContent(char* value);

