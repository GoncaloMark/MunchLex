/// \file   threading.c
/// \author Gonçalo Marques
/// \date   2024-01
#include "include/threading.h"
#include "include/tree.h"

/// @private
/// @brief A utility function to instantiate a new tpool_work_t object, allocating memory for a new work object.
/// @param func A function pointer to the function that shall be called.
/// @param args The args that shall be passed to the function.
static tpool_work_t* work_create(work_func_t func, void* args){
    if (func == NULL)
        return NULL;

    tpool_work_t* work = malloc(sizeof(tpool_work_t));
    if (work == NULL)
        return NULL;

    work->func = func;
    work->args = args;
    work->next = NULL;

    return work;
}

/// @private
/// @brief A Destructor function that simply frees the work unit from memory.
/// @param work Pointer to Work object.
static void work_destroy(tpool_work_t* work){
    if (work == NULL){
        return;
    }

    free(work);
}

/// @private
/// @brief A utility function that fetches a unit of work from the ThreadPool list, updating the work_first pointer to the next pointer of the previous work_first. Keeps integrity of list if it's the only item in list.
/// @param tp Pointer to ThreadPool Object.
static tpool_work_t* tpool_get_work(tpool_t* tp){
    printf("Getting work...\n");
    fflush(stdout);
    if(tp == NULL){
        printf("NULL POOL!!\n");
        return NULL;
    }

    tpool_work_t* workNow = tp->work_first;
    if(workNow == NULL){
        printf("NULL WORK!\n");
        return NULL;
    }

    if(workNow->next == NULL){
        tp->work_first = NULL;
        tp->work_last = NULL;
    } else {
        tp->work_first = workNow->next;
    }

    return workNow;
}

static void* tpool_worker(void* args) {
    tpool_t* tp = (tpool_t*) args;
    tpool_work_t* work;

    while (1) {
        pthread_mutex_lock(&(tp->work_mutex));

        while (tp->work_first == NULL && !tp->stop) {
            pthread_cond_wait(&(tp->work_cond), &(tp->work_mutex));
        }

        if (tp->stop && tp->work_first == NULL) {
            break;
        }

        work = tpool_get_work(tp);
        tp->working_cnt++;
        pthread_mutex_unlock(&(tp->work_mutex));

        if (work != NULL) {
            work->func(work->args);
            work_destroy(work);
        }

        pthread_mutex_lock(&(tp->work_mutex));
        tp->working_cnt--;
        if (!tp->stop && tp->working_cnt == 0 && tp->work_first == NULL) {
            pthread_cond_signal(&(tp->done_cond));
        }
        pthread_mutex_unlock(&(tp->work_mutex));
    }
    tp->thread_cnt--;
    pthread_cond_signal(&(tp->done_cond));
    pthread_mutex_unlock(&(tp->work_mutex));
    return NULL;
}

tpool_t* tpool_create(size_t num){
    pthread_t thread;

    if (num == 0) {
        num = 2;
    }

    tpool_t* tp = calloc(1, sizeof(tpool_t));
    if (tp == NULL)
        return NULL;

    tp->thread_cnt = num;

    pthread_mutex_init(&(tp->work_mutex), NULL);
    pthread_cond_init(&(tp->work_cond), NULL);
    pthread_cond_init(&(tp->done_cond), NULL);

    tp->work_first = NULL;
    tp->work_last  = NULL;
    tp->stop = false;

    for (size_t i = 0; i < num; i++) {
        pthread_create(&thread, NULL, tpool_worker, tp);
        pthread_detach(thread);
    }

    printf("ThreadPool Created...\n");

    return tp;
}

bool tpool_add_work(tpool_t* tp, work_func_t func, void* args){
    tpool_work_t* work;

    if (tp == NULL){
        return false;
    }

    work = work_create(func, args);
    if (work == NULL){
        return false;
    }

    pthread_mutex_lock(&(tp->work_mutex));
    if (tp->work_first == NULL) {
        tp->work_first = work;
        tp->work_last = tp->work_first;
    } else {
        tp->work_last->next = work;
        tp->work_last = work;
    }

    pthread_cond_broadcast(&(tp->work_cond));
    pthread_mutex_unlock(&(tp->work_mutex));
    printf("Work added...\n");
    return true;
}

void tpool_wait(tpool_t* tp) {
    if (tp == NULL){
        return;
    }
    pthread_mutex_lock(&(tp->work_mutex));
    while((!tp->stop && tp->working_cnt != 0) || (tp->stop && tp->thread_cnt != 0)) {
        pthread_cond_wait(&(tp->done_cond), &(tp->work_mutex));
    }
    pthread_mutex_unlock(&(tp->work_mutex));
}

void tpool_destroy(tpool_t* tp){
    if(tp == NULL){
        return;
    }

    pthread_mutex_lock(&(tp->work_mutex));
    tp->stop = true;
    pthread_cond_broadcast(&(tp->work_cond));
    pthread_mutex_unlock(&(tp->work_mutex));

    tpool_wait(tp);

    pthread_mutex_lock(&(tp->work_mutex));
    tpool_work_t* work;
    tpool_work_t* work_next;

    work = tp->work_first;
    while(work != NULL){
        work_next = work->next;
        work_destroy(work);
        work = work_next;
    }

    pthread_mutex_unlock(&(tp->work_mutex));

    pthread_mutex_destroy(&(tp->work_mutex));
    pthread_cond_destroy(&(tp->work_cond));
    pthread_cond_destroy(&(tp->done_cond));
}