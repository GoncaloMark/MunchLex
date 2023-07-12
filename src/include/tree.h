/// \file   parser.h
/// \author Gonçalo Marques
/// \date   2023-05

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "parser.h"

typedef struct TreeNode {
    token_type_t type;
    char* text_content;
    tree_t* parent;
    tree_t* child;
    tree_t* sibling;
} tree_t;

tree_t* createNode(token_type_t type, char* text_content);
void addChild(tree_t** parent, tree_t** child);
tree_t* searchNodeType(token_type_t type);
tree_t* searchNodeContent(char* text_content);
