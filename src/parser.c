/// \file   parser.c
/// \author Gonçalo Marques
/// \date   2024-01

#include "include/parser.h"
#include "include/tree.h"

/// @brief Reads line from a file or stream to the allocated line_t.
/// @param file Pointer to the file to read lines from.
static void read_lines(line_t* line, FILE* file){
    size_t line_buf_size = 0;

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file\n");
    }

    line->line_size = getline(&line->content, &line_buf_size, file);
}

/// @brief Returns a pointer to a token_t struct, reading from an input/line to be analysed.
/// @param input Pointer to the line to read tokens from.
/// @return token_t* (pointer to a token_t struct)
static token_t* lexer(const char* input){
    int prev_length = 0;
    token_t* token = malloc(sizeof(token_t));
    if (token == NULL)
        return NULL;

    while(*input){
        if(isspace(*input)) {
            input++;
            continue;
        }

        if(*input == '<'){
            if (*(input + 1) == '/') {
                token->type = TOKEN_TYPE_END;
                input += 2;
            } else {
                token->type = TOKEN_TYPE_TAG_NAME;
                input++;
            }
            token->start = input;
            while (*input && !isspace(*input) && *input != '>') {
                input++;
            }
            token->length = input - token->start;
            prev_length = token->length;
            return token;
        }
        
        const char* prev = (input - (prev_length + 1));
        
        if (*input == '>' && *prev != '/' && !isspace(*(input + 1))) {
            token->type = TOKEN_TYPE_TEXT;
            token->start = input + 1;
            
            while (*input && *input != '<') {
                input++;
            }

            token->length = input - token->start;
            return token;
        }
        input++;
    }
    token->type = TOKEN_TYPE_EOL;
    return token;
}

void munchLex(void* args){
    printf("Working...\n");
    params_t* s_params = (params_t*)args;

    FILE* file = fopen(s_params->filename, "r");
    token_t* token = NULL;

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", s_params->filename);
        return;
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
                if(token->type == TOKEN_TYPE_TAG_NAME || token->type == TOKEN_TYPE_TEXT) {
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

    printTree(head, 0, s_params->logFile); // Set 3rd argument to NULL if you want it printed on stout

    fclose(file);
    free(line->content);
    free(line);
    free(token);
    line = NULL;
    token = NULL;

    deleteTree(head);

    return;
}