/// \file   flagger.c
/// \author Gonçalo Marques
/// \date   2024-01

#include "include/flagger.h"

flagger_t* parseArgs(char** args, int length){
    if(args == NULL || length == 0){
        return NULL;
    }

    size_t capacity = (length / 2) + 1;

    flagger_t* flags = malloc(sizeof(flagger_t)*capacity);
    if(flags == NULL){
        return NULL;
    }

    size_t flagIndex = 0;
    for(int i = 0; i < length-1; i++){
        if (args[i][0] != '-') {
            continue;
        }

        char argVal = args[i][1];
        char* val = args[i+1];
        
        switch(argVal){
            case 'p':
                flags[flagIndex].key = ARG_TYPE_PARSER;
                flags[flagIndex].value = val;
                i++;
                flagIndex++;
                break;

            case 't':
                flags[flagIndex].key = ARG_TYPE_THREADS;
                flags[flagIndex].value = val;
                i++;
                flagIndex++;
                break;

            case 'f':
                i++;
                while (i < length && args[i][0] != '-') {
                    if (flagIndex >= capacity) {
                        capacity *= 2;
                        flagger_t* temp = realloc(flags, sizeof(flagger_t) * capacity);
                        if (temp == NULL) {
                            free(flags);
                            return NULL;
                        }
                        flags = temp;
                        temp = NULL;
                    }

                    flags[flagIndex].key = ARG_TYPE_FILE;
                    flags[flagIndex].value = args[i];
                    i++;
                    flagIndex++;
                }
                i--;
                break;
            
            default:
                free(flags);
                return NULL;
        }
    }   

    flagger_t* resizedFlags = realloc(flags, sizeof(flagger_t) * (flagIndex + 1));
    if (resizedFlags == NULL) {
        free(flags);
        return NULL;
    }
    flags = resizedFlags;

    flags[flagIndex].key = ARG_TYPE_END;
    flags[flagIndex].value = NULL;

    return flags;
}