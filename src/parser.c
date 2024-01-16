/// \file   parser.c
/// \author Gonçalo Marques
/// \date   2024-01

#include "include/parser.h"

void read_lines(line_t* line, FILE* file){
    size_t line_buf_size = 0;

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file\n");
    }

    line->line_size = getline(&line->content, &line_buf_size, file);
}

token_t* lexer(const char* input){
    static int prev_length;
    token_t* token = malloc(sizeof(token_t));
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
