/// \file   threading.c
/// \author Gonçalo Marques
/// \date   2023-05
#include "include/threading.h"

void* do_work(void* params){
    params_t* s_params = (params_t*)params;
    int tid = s_params->thread_id;
    printf("Thread %d started\n", tid);

    line_t* line;
    FILE* file = fopen(s_params->filename, "r");
    token_t token;

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", s_params->filename);
        return 0;
    }
    
    line = read_lines(file);
    const char* input = line->content;
    while(line->line_size > 0){
        printf("Content: %s\n", line->content);
        do {
            token = lexer(input);
            printf("Token type: %d, Token value: %.*s", token.type, token.length, token.start);
            putchar('\n');
            input = token.start + token.length;
        } while(token.type != TOKEN_TYPE_EOF);
        line = read_lines(file);
        input = line->content;
        if(line->line_size == -1) break;
    }

    fclose(file);
    free(line);
    line = NULL;

    printf("Thread %d finished\n", tid);

    return NULL;
}