/// \file   threading.c
/// \author Gonçalo Marques
/// \date   2023-05
#include "include/threading.h"

/* static char* string_from_pointer(const char* start, int length) {
    // Allocate memory for the string, plus space for the null terminator
    char* result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }
    strncpy(result, start, length);
    result[length] = '\0';
    return result;
} */

void* do_work(void* params){
    params_t* s_params = (params_t*)params;
    int tid = s_params->thread_id;
    printf("Thread %d started\n", tid);

    line_t* line = NULL;
    FILE* file = fopen(s_params->filename, "r");
    token_t* token = NULL;

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", s_params->filename);
        return 0;
    }
    
    line = read_lines(file);
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
        line = read_lines(file);
        input = line->content;
        if(line->line_size == -1) break;
    }

    fclose(file);
    free(line);
    free(token);
    line = NULL;

    printf("Thread %d finished\n", tid);

    return NULL;
}