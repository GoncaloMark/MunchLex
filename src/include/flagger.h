/// \file   flagger.h
/// \author Gonçalo Marques
/// \date   2024-01
#pragma once
#include <stdlib.h>

/// @brief An enum type that represents different types of arguments for this programs use case! Number of threads, parser type and identifies the files.
typedef enum ArgType {
    ARG_TYPE_THREADS,
    ARG_TYPE_PARSER,
    ARG_TYPE_FILE,
    ARG_TYPE_END
} arg_type_t;

/// @brief A struct type representing a CLI Flag, carrying an identifier Key of arg_type_t, and its char* value.
typedef struct Flagger {
    arg_type_t key;
    char* value;
} flagger_t;

/// @brief Function used to parse command line arguments, it takes the argv and its length and then it iteratively parses that array, allocates an array of flagger_t.
/// @param args Pointer to the CLI arguments in argv
/// @param length Length of this array (argv), basically argc
/// @returns An array of flagger_t.
flagger_t* parseArgs(char** args, int length);