/// \file   parser.h
/// \author Gonçalo Marques
/// \date   2023-05

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
    const char* content;
    size_t line_size;
} line_t;
//TODO: NEXT LINE? TO BE MORE EFFICIENT?

/// @brief Token - A struct type for representing a single token read from a file and/or stream.
typedef struct Token {
    token_type_t type;
    const char* start;
    int length;
} token_t;

/// @brief              - Returns a pointer to a line_t struct, reading from a file or stream.
/// @param file         - Pointer to the file to read lines from.
/// @return             - line_t* (pointer to a line_t struct)
line_t* read_lines(FILE* file);

/// @brief              - Returns a pointer to a token_t struct, reading from an input/line to be analysed.
/// @param input        - Pointer to the line to read tokens from.
/// @return             - token_t* (pointer to a token_t struct)
token_t* lexer(const char* input);

