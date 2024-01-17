/// \file   main.c
/// \author Gonçalo Marques
/// \date   2024-01

#include "include/threading.h"
#define MAX_THREADS 4

int main(int argc, char *argv[]){
    argc--;
    argv++;

    // if (argc < 1) return EXIT_FAILURE;
    // // pthread_t threads[argc];
    // char **filename = argv;

    // params_t params[argc];

    // // refactor to check if it gets a flag parse = daemon or parse = static
    // for(int i = 0; i < argc; i++){
    //     params[i].filename = filename[i];
    //     params[i].thread_id = i;
    //     // pthread_create(&threads[i], NULL, do_work, (void*)&params[i]);
    // }

    return 0;
}