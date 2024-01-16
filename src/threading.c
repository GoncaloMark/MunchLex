/// \file   threading.c
/// \author Gonçalo Marques
/// \date   2024-01
#include "include/threading.h"
#include "include/tree.h"

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

    tree_t* head = NULL;
    tree_t* current = head;
    tree_t* previous = NULL;

    while(line->line_size > 0){
        putchar('\n');
        printf("Content: %s\n", line->content);
        do {
            token = lexer(input);
            printf("Token type: %d, Token value: %.*s", token->type, (int)token->length, token->start);
            putchar('\n');

            tree_t* newNode = createNode(token->type, token->start, token->length);

            if(head == NULL){
                head = newNode;
                current = head;
            } else {
                if(token->type == TOKEN_TYPE_TAG_NAME) {
                    addChild(current, newNode);
                    previous = current;
                    current = newNode; 
                } else if(token->type == TOKEN_TYPE_END) {
                    current = previous;
                }
            }

            input = token->start + token->length;
        } while(token->type != TOKEN_TYPE_EOL);
        read_lines(line, file);
        input = line->content;
        if(line->line_size == -1) break;
    }

    printTree(head, 0);
    putchar('\n');

    fclose(file);
    free(line->content);
    free(line);
    free(token);
    line = NULL;
    token = NULL;

    deleteTree(head);

    printf("Thread %d finished\n", tid);
    sem_post(&semaphore);

    return NULL;
}