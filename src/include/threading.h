/// \file   threading.h
/// \author Gonçalo Marques
/// \date   2024-01
#pragma once
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "parser.h"
//#include <unistd.h>

/// @brief  - Global semaphore for parellelism control.
extern sem_t semaphore;

/// @brief  - Struct holding the parameters passed to the working thread.
typedef struct Params {
    char* filename;
    int thread_id;
} params_t;

/// @brief              - Executes the lexer/parser constructing the Tree Structure.
/// @param params       - Void pointer to be cast to params_t.
void* do_work(void* params);
