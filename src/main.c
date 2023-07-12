/// \file   main.c
/// \author Gonçalo Marques
/// \date   2023-05

#include "include/threading.h"
#define MAX_THREADS 4

int main(int argc, char *argv[]){
    argc--;
    argv++;

    if (argc < 1) return EXIT_FAILURE;
    pthread_t threads[MAX_THREADS];
    char **filename = argv;
    //element_t element;
    params_t params[MAX_THREADS];

    for(int i = 0; i < argc; i++){
        params[i].filename = filename[i];
        params[i].thread_id = i;

        pthread_create(&threads[i], NULL, do_work, (void*)&params[i]);
    }

    for(int i = 0; i < argc; i++){
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}