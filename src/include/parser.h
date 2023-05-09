#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef enum TokenType {
    TOKEN_TYPE_EOF,
    TOKEN_TYPE_END,
    TOKEN_TYPE_TAG_NAME,
    TOKEN_TYPE_ATTRIBUTE_NAME,
    TOKEN_TYPE_ATTRIBUTE_VALUE,
    TOKEN_TYPE_TEXT
} token_type_t;

typedef struct lineContent {
    const char* content;
    size_t line_size;
} line_t;

typedef struct Token {
    token_type_t type;
    const char* start;
    int length;
} token_t;

line_t* read_lines(char* filename, FILE* file);
token_t lexer(const char* input);

