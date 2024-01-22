/// \file   parser.h
/// \author Gonçalo Marques
/// \date   2024-01

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/// @brief Struct holding the parameters passed to the working thread.
typedef struct Params {
    char* filename;
    char* logFile;
} params_t;

/// @brief An enum type for representing different token types for the lexer to catalogue.
typedef enum TokenType {
    TOKEN_TYPE_EOL,
    TOKEN_TYPE_END,
    TOKEN_TYPE_TAG_NAME,
    TOKEN_TYPE_ATTRIBUTE_NAME,
    TOKEN_TYPE_ATTRIBUTE_VALUE,
    TOKEN_TYPE_TEXT
} token_type_t;


/// @brief A struct type for representing the content of a line, read from a file and/or stream.
typedef struct lineContent {
    char* content;
    ssize_t line_size;
} line_t;
//TODO: Buffer NEXT LINE? TO BE MORE EFFICIENT?

/// @brief A struct type for representing a single token read from a file and/or stream.
typedef struct Token {
    token_type_t type;
    const char* start;
    size_t length;
} token_t;

/// @brief Function used to lex and parse the HTML language into a Syntax Tree, this is the work function that will be published to the thread pool work list, arguments will be dynamic this way.
/// @param params A void pointer to be cast to params_t
void munchLex(void* args);

