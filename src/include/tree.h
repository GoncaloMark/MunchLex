/// \file   parser.h
/// \author Gonçalo Marques
/// \date   2024-01

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "parser.h"

/// @brief  - TreeNode type holds information regarding a Node.
typedef struct TreeNode tree_t;

struct TreeNode {
    token_type_t type;
    char* content;
    tree_t* parent;
    size_t children_count;
    tree_t** children;
};

/// @brief              - Returns a pointer to a tree_t struct, after parsing the line it constructs the node element.
/// @param type         - Type of the Token.
/// @param value        - Value to be written to the content of the Node.
/// @return             - tree_t* (pointer to an allocated tree_t struct)
tree_t* createNode(token_type_t type, const char* start, size_t length);

/// @brief              - Add a child to the elements children array.
/// @param parent       - Parent Node tree_t.
/// @param child        - Child Node tree_t.
void addChild(tree_t* parent, tree_t* child);

/// @brief              - Delete the whole tree recursively.
/// @param head         - Head Node tree_t.
void deleteTree(tree_t* head);

/// @brief              - Print the whole tree recursively.
/// @param node         - Node tree_t where it starts.
/// @param depth        - Depth is the initial white space (default to 0).
void printTree(const tree_t* node, int depth);

tree_t* searchNodeType(token_type_t type);

tree_t* searchNodeContent(char* value);

