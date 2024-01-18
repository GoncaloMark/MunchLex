/// \file   main.c
/// \author Gonçalo Marques
/// \date   2024-01

#include "include/threading.h"
#include "include/flagger.h"
#include <string.h>

int main(int argc, char *argv[]){
    argc--;
    argv++;

    if (argc < 2) return EXIT_FAILURE;

    flagger_t* flags = parseArgs(argv, argc);
    if (flags == NULL) return EXIT_FAILURE;

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
                    return EXIT_FAILURE;
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
    printf("File Names:\n");

    for(int i=0; flags[i].key == ARG_TYPE_FILE; i++){
        params[i].filename = flags[i].value;
        printf("%s\n", params[i].filename);
    }
    free(flags);
    return 0;
}