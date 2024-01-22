/// \file   main.c
/// \author Gonçalo Marques
/// \date   2024-01

#include "include/threading.h"
#include "include/flagger.h"
#include <string.h>

int main(int argc, char *argv[]){
    argc--;
    argv++;

    if (argc < 2){
        return EXIT_FAILURE;
    } 

    flagger_t* flags = parseArgs(argv, argc);
    if (flags == NULL){
        return EXIT_FAILURE;
    } 

    bool hasFileFlag = false;
    int threads = 2;
    bool daemonFlag = false;
    size_t files = 0;

    for (int i = 0; flags[i].key != ARG_TYPE_END; i++) {
        switch (flags[i].key) {
            case ARG_TYPE_FILE:
                hasFileFlag = true;
                files++;
                break;
            case ARG_TYPE_THREADS:
                threads = atoi(flags[i].value);
                if(threads == 0){
                    threads = 2;
                }
                break;
            case ARG_TYPE_PARSER:
                daemonFlag = (strcmp(flags[i].value, "Daemon") == 0);
                break;
            case ARG_TYPE_END:
                break;
        }
    }

    if (!hasFileFlag) {
        fprintf(stderr, "Error: Missing mandatory -f flag.\n");
        free(flags);
        return EXIT_FAILURE;
    }

    params_t params[files];

    if(daemonFlag){
        printf("Daemon mode not implemented :(\n");
        return 0;
    }

    printf("Create pool with %d threads.\n", threads);
    printf("Number of Files: %ld.\n", files);

    for(int i=0; flags[i].key == ARG_TYPE_FILE; i++){
        params[i].filename = flags[i].value;

        size_t logFileSize = strlen(params[i].filename) + strlen("_log.txt") + 1;
        params[i].logFile = malloc(logFileSize * sizeof(char));
        if (params[i].logFile == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for logFile.\n");
            free(flags);
            for (int j = 0; j < i; j++) {
                free(params[j].logFile);
            }
            return EXIT_FAILURE;
        }

        sprintf(params[i].logFile, "%s_log.txt", flags[i].value);
        printf("Filename: %s\n", params[i].filename);
        printf("LogFile: %s\n", params[i].logFile);

        FILE* fp = fopen(params[i].logFile, "w");
        if (fp == NULL) {
            perror("Unable to create log file");
            return EXIT_FAILURE;
        }

        fprintf(fp, "Log Start\n");

        fclose(fp);
    }

    printf("Log directory and files created successfully.\n");

    free(flags);

    tpool_t* tp;
    tp = tpool_create(threads);

    for(size_t i=0; i<files; i++){
        bool success = tpool_add_work(tp, munchLex, (void*) &params[i]);
        if(!success){
            printf("Couldn't add work\n");
            return EXIT_FAILURE;
        }
    }

    tpool_wait(tp);

    tpool_destroy(tp);

    for(size_t i=0; i<files; i++){
        free(params[i].logFile);
    }

    return 0;
}