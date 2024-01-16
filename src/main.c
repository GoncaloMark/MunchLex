/// \file   main.c
/// \author Gonçalo Marques
/// \date   2024-01

#include "include/threading.h"
#define MAX_THREADS 4

sem_t semaphore;
int main(int argc, char *argv[]){
    argc--;
    argv++;

    sem_init(&semaphore, 0, MAX_THREADS);

    if (argc < 1) return EXIT_FAILURE;
    pthread_t threads[argc];
    char **filename = argv;

    params_t params[argc];

    for(int i = 0; i < argc; i++){
        params[i].filename = filename[i];
        params[i].thread_id = i;
        pthread_create(&threads[i], NULL, do_work, (void*)&params[i]);
    }
    for(int i = 0; i < argc; i++){
        pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&semaphore);

    return 0;
}