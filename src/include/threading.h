/// \file   threading.h
/// \author Gonçalo Marques
/// \date   2023-05
#pragma once
#include <stdio.h>
#include <pthread.h>
#include "parser.h"
//#include <unistd.h>

typedef struct Params {
    char* filename;
    int thread_id;
} params_t;

void* do_work(void* params);
