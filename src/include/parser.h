/// \file   parser.h
/// \author Gonçalo Marques
/// \date   2024-01

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/// @brief Token Type - An enum type for representing different token types for the lexer to catalogue.
typedef enum TokenType {
    TOKEN_TYPE_EOL,
    TOKEN_TYPE_END,
    TOKEN_TYPE_TAG_NAME,
    TOKEN_TYPE_ATTRIBUTE_NAME,
    TOKEN_TYPE_ATTRIBUTE_VALUE,
    TOKEN_TYPE_TEXT
} token_type_t;


/// @brief Line Content - A struct type for representing the content of a line, read from a file and/or stream.
typedef struct lineContent {
    char* content;
    ssize_t line_size;
} line_t;
//TODO: NEXT LINE? TO BE MORE EFFICIENT?

/// @brief Token - A struct type for representing a single token read from a file and/or stream.
typedef struct Token {
    token_type_t type;
    const char* start;
    int length;
} token_t;

/// @brief              - Reads line from a file or stream to the allocated line_t.
/// @param file         - Pointer to the file to read lines from.
void read_lines(line_t* line, FILE* file);

/// @brief              - Returns a pointer to a token_t struct, reading from an input/line to be analysed.
/// @param input        - Pointer to the line to read tokens from.
/// @return             - token_t* (pointer to a token_t struct)
token_t* lexer(const char* input);

