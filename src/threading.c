/// \file   threading.c
/// \author Gonçalo Marques
/// \date   2024-01
#include "include/threading.h"

void* do_work(void* params){
    sem_wait(&semaphore);

    params_t* s_params = (params_t*)params;
    int tid = s_params->thread_id;
    printf("Thread %d started\n", tid);

    FILE* file = fopen(s_params->filename, "r");
    token_t* token = NULL;

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", s_params->filename);
        return 0;
    }

    line_t* line = malloc(sizeof(line_t));
    line->line_size = 0;
    line->content = NULL;
    
    read_lines(line, file);
    const char* input = line->content;
    while(line->line_size > 0){
        putchar('\n');
        printf("Content: %s\n", line->content);
        do {
            token = lexer(input);
            printf("Token type: %d, Token value: %.*s", token->type, token->length, token->start);
            putchar('\n');
            input = token->start + token->length;
        } while(token->type != TOKEN_TYPE_EOL);
        read_lines(line, file);
        input = line->content;
        if(line->line_size == -1) break;
    }

    fclose(file);
    free(line->content);
    free(line);
    free(token);
    line = NULL;
    token = NULL;

    printf("Thread %d finished\n", tid);
    sem_post(&semaphore);

    return NULL;
}