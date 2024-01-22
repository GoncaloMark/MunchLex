/// \file   threading.h
/// \author Gonçalo Marques
/// \date   2024-01
#pragma once
#include <stdio.h>
#include <pthread.h>
#include "parser.h"
#include <stdbool.h>
#include <stddef.h>

/// @brief Forward declaration of the WorkLoad Struct.
typedef struct WorkLoad tpool_work_t;

/// @brief Function Pointer represents the worker function (munchLex) to be added to the work list of the thread pool.
typedef void (*work_func_t)(void* args);

/// @brief Struct holding the worker function, its arguments that shall be used when calling it and a pointer to the next unit of work.
struct WorkLoad {
    work_func_t         func;
    void*               args;
    tpool_work_t*       next;
};

/// @brief Struct representing a ThreadPool object.
typedef struct ThreadPool{ 
    tpool_work_t*       work_first;     // A pointer to the unit of work to be processed (updated every time we get work with its next pointer).
    tpool_work_t*       work_last;      // A pointer keeping a reference to the last element added to the list (so we can later update its next pointer).
    pthread_mutex_t     work_mutex;     // Mutex controlling the access to the ThreadPool members.
    pthread_cond_t      work_cond;      // Condition to signal that there's work to be consumed.
    pthread_cond_t      done_cond;      // Condition to signal that the work is done processing.
    size_t              working_cnt;    // Counter that keeps track of the number of threads currently actively working.
    size_t              thread_cnt;     // Number of spawned threads on the Pool.
    bool                stop;           // Flag to shutdown the ThreadPool if needed.
} tpool_t;

/// @brief A constructor function that allocates a new ThreadPool Object.
/// @param num Number of threads to spawn in the Pool.
tpool_t* tpool_create(size_t num);
void tpool_destroy(tpool_t* tp);

bool tpool_add_work(tpool_t* tp, work_func_t func, void* args);
void tpool_wait(tpool_t* tp);